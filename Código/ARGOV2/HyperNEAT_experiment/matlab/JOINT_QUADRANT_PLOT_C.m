function [y] = JOINT_QUADRANT_PLOT_C()

x = '../bin/simulation_files/joints_position/Champion.txt';
Title = 'Position of Joint ';

A = importdata(x, '\t');

t = A(:,1);

figure

for i = 2 : 13,
	y = [Title num2str(i-1)];
	subplot(4,3,i-1);
	plot(t, A(:,i), 'Color', 'b', 'LineWidth',2);
	title(y)
	xlabel('Time [s]')
	ylabel('Joint Position [rad]')
end

end

