clc; close all;

Kp = 1;
Kd = 0.1;
Ki = 0;
%%

%mdl = "PIDtuning";
%load_system(mdl);
%set_param(mdl, "StopTime", "4");
%set_param(mdl, "SimulationCommand", "start");

time = ScopeData.time;

pwm = ScopeData.signals(1).values;

enble = ScopeData.signals(2).values;