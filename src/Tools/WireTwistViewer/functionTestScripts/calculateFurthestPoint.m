%% --- VARIABLE SIZE STRESS TESTER ---
clear; clc; close all;

% 1. Setup a smaller Core
circleCore = struct('x', 0, 'y', 0, 'r', 4);

% 2. Initialize
circleList = [];    
circlePrev = [];    

% 3. Generate 20 random wire radii between 2.5mm and 3.5mm
% (rand generates 0-1, so this scales it)
wireRadii = 2.5 + (3.5-2.5) .* rand(1, 20); 

% 4. Setup Plot
figure('Color', 'w');
viscircles([circleCore.x, circleCore.y], circleCore.r, 'EdgeColor', 'k', 'LineWidth', 2);
hold on; 
axis equal;
grid on;
title('Variable stress test');

% 5. The Greedy Loop
for i = 1:length(wireRadii)
    trialWire = struct('r', wireRadii(i));
    
    % Try to place the wire
    [newWire, success] = addCircle(circleCore, circlePrev, trialWire, circleList, 'b');
    
    if success
        circleList = [circleList, newWire]; 
        circlePrev = newWire;
        fprintf('Wire %d (r=%.2f) placed.\n', i, wireRadii(i));
    else
        % This is the "Safety Valve"
        fprintf('Wire %d (r=%.2f) FAILED: Overlap with Wire 1. Necklace Closed.\n', i, wireRadii(i));
        break; 
    end
end


function [circleCurrent, success] = addCircle(circleCore, circlePrev, circleCurrent, circleList, circleColor)
    % circleCore: struct with [x, y, r]
    % circlePrev: struct with [x, y, r] (or empty if first wire)
    % circleCurrent: struct with [r] (x and y will be calculated)

    success = false; % Assume failure until proven otherwise

    % 1. Handle the "First Wire" case
    if isempty(circlePrev)
        % This function will determine the starting position (e.g., at the top)
        % and call the plot command.
        circleCurrent = buildFirst(circleCore, circleCurrent);
        success = true; 
        return; % Exit function after placing first
    end

    % 2. Calculate the number of intersections (nOI)
    circleCurrent = calculateCircle(circleCore, circlePrev, circleCurrent);
    isValid = isFit(circleCurrent, circleList, circleCore);

    % 3. Placement Logic
    if isValid
        % This function will calculate the specific (x,y), update the 
        % circleCurrent struct, and plot it.
        plotCircle(circleCurrent, circleColor);
        success = true; % Mark as a valid placement
    else
        % If it doesn't fit, success stays false. 
        % We don't even need an 'else return' here; 
        % the function will just finish naturally.
    end
end

% Placeholder for the 'pass' logic to prevent MATLAB errors
function pass()
    % Do nothing
end

function circleCurrent = calculateCircle(circleCore, circlePrev, circleCurrent)
    % 1. Extract dimensions
    r1 = circleCore.r;
    r2 = circlePrev.r;
    r3 = circleCurrent.r;

    % Distances for the triangle sides
    R1 = r1 + r3; % Core to Current
    R2 = r2 + r3; % Prev to Current
    
    % 2. Calculate distance between existing centers (d)
    dx = circlePrev.x - circleCore.x;
    dy = circlePrev.y - circleCore.y;
    d = sqrt(dx^2 + dy^2);

    % 3. Triangle Geometry (The "Rearranged" Law of Cosines)
    % Projection distance along the line d
    a = (R1^2 - R2^2 + d^2) / (2 * d);
    
    % Perpendicular height
    % We use max(0, ...) to ensure that if floating-point errors make the
    % value slightly negative (e.g., -1e-15), sqrt doesn't return an imaginary number.
    h = sqrt(max(0, R1^2 - a^2)); 

    % 4. Find the Base Point (P_base) and Unit Vectors
    ux = dx / d; % Unit vector along the d-line
    uy = dy / d;
    
    x_base = circleCore.x + a * ux;
    y_base = circleCore.y + a * uy;

    % 5. Generate the two possible intersection points
    % Option 1: Positive rotation
    P1_x = x_base - h * uy;
    P1_y = y_base + h * ux;
    
    % Option 2: Negative rotation
    P2_x = x_base + h * uy;
    P2_y = y_base - h * ux;

    % 6. The "In-Depth" Choice: 2D Cross Product for CCW Orientation
    % Vector A: Core center to Previous wire center
    % Vector B: Core center to Potential New center (P1)
    Ax = circlePrev.x - circleCore.x;
    Ay = circlePrev.y - circleCore.y;
    
    B1x = P1_x - circleCore.x;
    B1y = P1_y - circleCore.y;

    % Calculate Z (The 2D Cross Product)
    Z = (Ax * B1y) - (Ay * B1x);

    % Selection: If Z > 0, P1 is to the LEFT of A (Counter-Clockwise)
    if Z > 0
        circleCurrent.x = P1_x;
        circleCurrent.y = P1_y;
    else
        circleCurrent.x = P2_x;
        circleCurrent.y = P2_y;
    end

end

function circleCurrent = buildFirst(circleCore, circleCurrent)
    % 1. Calculate the North position
    % The x-coordinate stays the same as the Core
    circleCurrent.x = circleCore.x;
    
    % The y-coordinate is the Core center plus both radii
    circleCurrent.y = circleCore.y + circleCore.r + circleCurrent.r;

    % 2. Plotting (Your #plot comment)
    % Draw the circle and mark the center point
    viscircles([circleCurrent.x, circleCurrent.y], circleCurrent.r, 'EdgeColor', 'g');
    hold on;
    plot(circleCurrent.x, circleCurrent.y, 'k+');
    
    % Optional: Add a label to indicate it's the start of the chain
    text(circleCurrent.x, circleCurrent.y + circleCurrent.r, ' Start', 'FontSize', 8);
end

function isValid = isFit(circleCurrent, circleList, circleCore)
    % Default to true
    isValid = true;
    
    % Combine all obstacles
    allObstacles = [circleCore, circleList];
    
    % Tolerance for floating point math
    tol = 1e-9; 

    for i = 1:length(allObstacles)
        dx = circleCurrent.x - allObstacles(i).x;
        dy = circleCurrent.y - allObstacles(i).y;
        dist = sqrt(dx^2 + dy^2);
        
        sumR = circleCurrent.r + allObstacles(i).r;
        
        % Check for overlap
        % If distance is significantly less than the sum of radii, they overlap.
        if dist < (sumR - tol)
            isValid = false;
            return; % Exit early for efficiency
        end
    end
end

function plotCircle(circleCurrent, color)
    % Draw the perimeter
    viscircles([circleCurrent.x, circleCurrent.y], circleCurrent.r, 'EdgeColor', color);
    hold on;
    % Mark the center for harness routing alignment
    plot(circleCurrent.x, circleCurrent.y, 'k+'); 
end