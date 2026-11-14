% This file will plot the data obtained by simulink during the PID tuning.
% The encoder positions have been squeezed on simulink as 1-D array.
% Two subplot will be generated one for the full data of PWM and Position, 
% and one for the zoomed version of them.

clc;
clear;
close all;

load(fullfile("squeezed", "PID_kp1_kd0_ki0.mat"))
pwm1 = scope.signals(1).values;
position1 = scope.signals(2).values;
t = scope.time;

load(fullfile("squeezed", "PID_kp05_kd0_ki0.mat"))
pwm2 = scope.signals(1).values;
position2 = scope.signals(2).values;

load(fullfile("squeezed", "PID_kp05_kd01_ki0.mat"))
pwm3 = scope.signals(1).values;
position3 = scope.signals(2).values;

load(fullfile("squeezed", "PID_kp05_kd005_ki0_best.mat"))
pwm4 = scope.signals(1).values;
position4 = scope.signals(2).values;

% Figure settings used by the plotting code
W_frame1 = 20;
H_frame1 = 20.6;
LLC_frame1 = [5, 5];

AxisFontSize = 18;
LW1 = 2;

% Shared legend labels
pidLabels = {"Kp=1, Kd=0, Ki=0", ...
             "Kp=0.5, Kd=0, Ki=0", ...
             "Kp=0.5, Kd=0.1, Ki=0", ...
             "Kp=0.5, Kd=0.05, Ki=0"};

% Create the full-range figure with two subplots
figPidSub = figure;
figPidSub.Units = "centimeters";
figPidSub.Position = [LLC_frame1, W_frame1, H_frame1];

tl1 = tiledlayout(figPidSub, 2, 1, ...
    "TileSpacing", "compact", "Padding", "compact");

% Full-range position subplot
ax1 = nexttile(tl1);
hold(ax1, "on");

p1 = plot(ax1, t, position1, "r-", "LineWidth", LW1);
p2 = plot(ax1, t, position2, "b-", "LineWidth", LW1);
p3 = plot(ax1, t, position3, "g-", "LineWidth", LW1);
p4 = plot(ax1, t, position4, "k-", "LineWidth", LW1);

ylabel(ax1, "Encoder Position");
xlim(ax1, [min(t), max(t)]);
ylim(ax1, [0, 5000]);
ax1.YTick = 0:1000:5000;
ax1.FontName = "Times New Roman";
ax1.FontSize = AxisFontSize;
ax1.GridLineStyle = "--";
grid(ax1, "on");
box(ax1, "on");
legend(ax1, [p1, p2, p3, p4], pidLabels, ...
    "Location", "southeast");

% Full-range PWM subplot
ax2 = nexttile(tl1);
hold(ax2, "on");

plot(ax2, t, pwm1, "r-", "LineWidth", LW1);
plot(ax2, t, pwm2, "b-", "LineWidth", LW1);
plot(ax2, t, pwm3, "g-", "LineWidth", LW1);
plot(ax2, t, pwm4, "k-", "LineWidth", LW1);

xlabel(ax2, "Time [s]");
ylabel(ax2, "PWM");
xlim(ax2, [min(t), max(t)]);
ylim(ax2, [0, 255]);
ax2.FontName = "Times New Roman";
ax2.FontSize = AxisFontSize;
ax2.GridLineStyle = "--";
grid(ax2, "on");
box(ax2, "on");
legend(ax2, pidLabels, "Location", "southeast");

% assign a folder where to create the images
outputFolder = fullfile(fileparts(mfilename("fullpath")), "subplot");
if ~isfolder(outputFolder)
    mkdir(outputFolder);
end

% save the file in the new folder
saveas(figPidSub, fullfile(outputFolder, "PID_Tuning_Sub.jpg"), ...
    "jpeg");
saveas(figPidSub, fullfile(outputFolder, "PID_Tuning_Sub.eps"), ...
    "epsc2");

% Create the zoomed figure with two subplots
figPidZoomSub = figure;
figPidZoomSub.Units = "centimeters";
figPidZoomSub.Position = [LLC_frame1, W_frame1, H_frame1];

tl2 = tiledlayout(figPidZoomSub, 2, 1, ...
    "TileSpacing", "compact", "Padding", "compact");

% Zoomed position subplot
ax3 = nexttile(tl2);
hold(ax3, "on");

plot(ax3, t, position1, "r-", "LineWidth", LW1);
plot(ax3, t, position2, "b-", "LineWidth", LW1);
plot(ax3, t, position3, "g-", "LineWidth", LW1);
plot(ax3, t, position4, "k-", "LineWidth", LW1);

ylabel(ax3, "Encoder Position");
xlim(ax3, [1.1, 2.7]);
ylim(ax3, [3500, 4200]);
ax3.FontName = "Times New Roman";
ax3.FontSize = AxisFontSize;
ax3.GridLineStyle = "--";
grid(ax3, "on");
box(ax3, "on");
legend(ax3, pidLabels, "Location", "best");

% Zoomed PWM subplot
ax4 = nexttile(tl2);
hold(ax4, "on");

plot(ax4, t, pwm1, "r-", "LineWidth", LW1);
plot(ax4, t, pwm2, "b-", "LineWidth", LW1);
plot(ax4, t, pwm3, "g-", "LineWidth", LW1);
plot(ax4, t, pwm4, "k-", "LineWidth", LW1);

xlabel(ax4, "Time [s]");
ylabel(ax4, "PWM");
xlim(ax4, [1.1, 2.7]);
ylim(ax4, [90, 210]);
ax4.FontName = "Times New Roman";
ax4.FontSize = AxisFontSize;
ax4.GridLineStyle = "--";
grid(ax4, "on");
box(ax4, "on");
legend(ax4, pidLabels, "Location", "best");


saveas(figPidZoomSub, fullfile(outputFolder, "PID_Tuning_Zoom_Sub.jpg"), ...
    "jpeg");
saveas(figPidZoomSub, fullfile(outputFolder, "PID_Tuning_Zoom_Sub.eps"), ...
    "epsc2");
