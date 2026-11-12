clear; clc; close all;

fntSize = 18;

set(groot, 'defaultAxesFontName', 'Times New Roman', ...
    'defaultAxesFontSize', fntSize, ...
    'defaultTextFontName', 'Times New Roman', ...
    'defaultTextFontSize', fntSize, ...
    'defaultLegendFontName', 'Times New Roman', ...
    'defaultLegendFontSize',fntSize);

% Time in seconds
moveTime = [0.106, 19.021, 35.844, 54.744, 71.672, 90.686, 107.508];
stopTime = [6.684, 23.536, 42.362, 59.261, 78.250, 95.199, 114.025];
stopFloor = [3, 4, 2, 1, 3, 4, 2];

% Build the elevator floor trace, including stationary periods.
timeFloor = 0;
elevatorFloor = 1;
for k = 1:numel(moveTime)
    timeFloor(end+1) = moveTime(k); %#ok<SAGROW>
    elevatorFloor(end+1) = elevatorFloor(end); %#ok<SAGROW>
    timeFloor(end+1) = stopTime(k); %#ok<SAGROW>
    elevatorFloor(end+1) = stopFloor(k); %#ok<SAGROW>
end

% Button presses: time in seconds and requested floor.
buttonTime = [0, 8.837, 9.393, 42.412, 44.903, 71.565, 80.401];
buttonFloor = [3, 4, 2, 1, 4, 3, 2];

figure1 = figure('Color', 'w');
plot(timeFloor, elevatorFloor, '-o', ...
    'Color', [0.13 0.40 0.67], ...
    'LineWidth', 2, ...
    'MarkerSize', 5, ...
    'MarkerFaceColor', [0.13 0.40 0.67]);
hold on;
scatter(buttonTime, buttonFloor, 65, [0.78 0.34 0.08], 'd', 'filled');

xlabel('Time [s]', 'FontName', 'Times New Roman', 'FontSize', fntSize);
ylabel('Floor', 'FontName', 'Times New Roman', 'FontSize', fntSize);
yticks(1:4);
ylim([0.7 4.3]);

% Add a small horizontal margin before the first and after the last event.
plotEnd = max([timeFloor, buttonTime]);
xMargin = 0.03 * plotEnd;
xlim([-xMargin, plotEnd + xMargin]);

grid on;
legend('Elevator movement', 'Floor request', 'Location', 'southeast');
hold off;


saveas(figure1, "Elevator_movement_plot.jpeg", "jpeg");
saveas(figure1, "Elevator_movement_plot.eps", "epsc2");
