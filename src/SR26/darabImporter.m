% Load CSV
data = readtable('20251206_curr.csv');

% Convert to numeric arrays
time = data.xtime_s_;  % [s]
c = data.PM_dcBusCurrent_A_;
ct = data.PM_commandedTorque_Nm_;
volt = data.PM_dcBusVolt_V_;
spd = data.PM_motorSpeed_rpm_;
ft = data.PM_torqueFeedback_Nm_;

current_input2 = timeseries([c, ct, volt, spd, ft], time);