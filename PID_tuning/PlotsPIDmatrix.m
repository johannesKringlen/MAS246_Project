% This file will plot the data obtained by simulink during the PID tuning.
% The encoder positions have been sent as matrix and squeezed in this file.
% Four plot will be generated two for the full data of PWM and Position, 
% two for the zoomed version of them.

clc;
clear;
close all;

load(fullfile("matrix", "PID_kp1_kd0_ki0.mat"))
pwm1 = scope.signals(1).values;
position1 = squeeze(scope.signals(2).values);
t = scope.time;

load(fullfile("matrix", "PID_kp05_kd0_ki0.mat"))
pwm2 = scope.signals(1).values;
position2 = squeeze(scope.signals(2).values);
 
load(fullfile("matrix", "PID_kp05_kd01_ki0.mat"))
pwm3 = scope.signals(1).values;
position3 = squeeze(scope.signals(2).values);

load(fullfile("matrix", "PID_kp05_kd005_ki0_best.mat"))
pwm4 = scope.signals(1).values;
position4 = squeeze(scope.signals(2).values);

figPidTuning = figure;
ax1 = gca;

W_frame1 = 20;
H_frame1 = 10.3;
LLC_frame1 = [5, 5];
W_axis1 = 16;
H_axis1 = 7;
LLC_axis1 = [3.5, 2.1];

xlabel_x = W_axis1 / 2;
xlabel_y = -1;
ylabel_x = -1.7;
ylabel_y = H_axis1 / 2;


AxisFontSize = 24;
LW1 = 2;

figPidTuning.Units = "centimeters";
figPidTuning.Position = [LLC_frame1, W_frame1, H_frame1];

% Plot the PID comparison
hold(ax1, "on");

plt1 = plot(ax1, t, position1, "r-",  "LineWidth", LW1);
plt2 = plot(ax1, t, position2, "b-", "LineWidth", LW1);
plt3 = plot(ax1, t, position3, "g-", "LineWidth", LW1);
plt4 = plot(ax1, t, position4, "k-",  "LineWidth", LW1);

ylabel(ax1, "Encoder Position");

ax1.Units = "centimeters";
ax1.GridLineStyle = "--";
ax1.Position = [LLC_axis1, W_axis1, H_axis1];
ax1.FontName = "Times New Roman";
ax1.FontSize = AxisFontSize;
ax1.XTick = min(t):0.5:max(t);
ax1.YTick = 0:1000:5000;

axis(ax1, [min(t), max(t), 0, 5000]);

grid(ax1, "on");
box(ax1, "on");

label_x1 = xlabel("Time [s]");
label_x1.Units = "centimeters";
label_x1.Position = [xlabel_x, xlabel_y, 0];

leg1 = legend(ax1, [plt1, plt2, plt3, plt4], ...
    {"Kp=1, Kd=0, Ki=0", ...
    "Kp=0.5, Kd=0, Ki=0", ...
    "Kp=0.5, Kd=0.1, Ki=0", ...
    "Kp=0.5, Kd=0.05, Ki=0"}, ...
    "Location", "southeast");

saveas(figPidTuning, "PID_Tuning2.jpg", "jpeg");
saveas(figPidTuning, "PID_Tuning2.eps", "epsc2");

% Plot a zoomed version of PID comparison


figPidZoom = figure;
ax2 = axes(figPidZoom);

figPidZoom.Units = "centimeters";
figPidZoom.Position = [LLC_frame1, W_frame1, H_frame1];

hold(ax2, "on");

plot(ax2, t, position1, "r-",  "LineWidth", LW1);
plot(ax2, t, position2, "b-", "LineWidth", LW1);
plot(ax2, t, position3, "g-", "LineWidth", LW1);
plot(ax2, t, position4, "k-",  "LineWidth", LW1);

xlim(ax2, [1.1, 2.7]);
ylim(ax2, [3500, 4200]);

xlabel(ax2, "Time [s]");
ylabel(ax2, "Encoder Position");
legend(ax2, ...
    {"Kp=1, Kd=0, Ki=0", ...
    "Kp=0.5, Kd=0, Ki=0", ...
    "Kp=0.5, Kd=0.1, Ki=0", ...
    "Kp=0.5, Kd=0.05, Ki=0"}, ...
    "Location", "best");

ax2.FontName = "Times New Roman";
ax2.FontSize = AxisFontSize;
ax2.GridLineStyle = "--";
grid(ax2, "on");
box(ax2, "on");
hold(ax2, "off");

saveas(figPidTuning, "PID_TuningZoom2.jpg", "jpeg");
saveas(figPidTuning, "PID_TuningZoom2.eps", "epsc2");

% Plot PWM comparison

figPwm = figure;
figPwm.Units = "centimeters";
figPwm.Position = [LLC_frame1, W_frame1, H_frame1];

ax3 = axes(figPwm);
hold(ax3, "on");

plot(ax3, t, pwm1, "r-",  "LineWidth", LW1);
plot(ax3, t, pwm2, "b-", "LineWidth", LW1);
plot(ax3, t, pwm3, "g-", "LineWidth", LW1);
plot(ax3, t, pwm4, "k-",  "LineWidth", LW1);

xlim(ax3, [min(t), max(t)]);
ylim(ax3, [90, 210]);

xlabel(ax3, "Time [s]");
ylabel(ax3, "PWM");

legend(ax3, ...
    {"Kp=1, Kd=0, Ki=0", ...
    "Kp=0.5, Kd=0, Ki=0", ...
    "Kp=0.5, Kd=0.1, Ki=0", ...
    "Kp=0.5, Kd=0.05, Ki=0"}, ...
    "Location", "best");

ax3.FontName = "Times New Roman";
ax3.FontSize = AxisFontSize;
ax3.GridLineStyle = "--";
grid(ax3, "on");
box(ax3, "on");
hold(ax3, "off");

saveas(figPidTuning, "PID_TuningPWM2.jpg", "jpeg");
saveas(figPidTuning, "PID_TuningPWM2.eps", "epsc2");

% Plot a zoomed version for PWM comparison

figPwmZoom = figure;
figPwmZoom.Units = "centimeters";
figPwmZoom.Position = [LLC_frame1, W_frame1, H_frame1];

ax4 = axes(figPwmZoom);
hold(ax4, "on");

plot(ax4, t, pwm1, "r-",  "LineWidth", LW1);
plot(ax4, t, pwm2, "b-", "LineWidth", LW1);
plot(ax4, t, pwm3, "g-", "LineWidth", LW1);
plot(ax4, t, pwm4, "k-",  "LineWidth", LW1);

xlim(ax4, [1.1, 2.7]);
ylim(ax4, [90, 210]);

xlabel(ax4, "Time [s]");
ylabel(ax4, "PWM");

legend(ax4, ...
    {"Kp=1, Kd=0, Ki=0", ...
    "Kp=0.5, Kd=0, Ki=0", ...
    "Kp=0.5, Kd=0.1, Ki=0", ...
    "Kp=0.5, Kd=0.05, Ki=0"}, ...
    "Location", "best");

ax4.FontName = "Times New Roman";
ax4.FontSize = AxisFontSize;
ax4.GridLineStyle = "--";
grid(ax4, "on");
box(ax4, "on");
hold(ax4, "off");

saveas(figPidTuning, "PID_TuningPWMZoom2.jpg", "jpeg");
saveas(figPidTuning, "PID_TuningPWMZoom2.eps", "epsc2");