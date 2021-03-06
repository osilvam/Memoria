function [y] = JOINT_QUADRANT_PLOT(g,p)

plot_order = [1 2 4 5 7 8 10 11 12];

S0 = '../bin/simulation_files/joints_position/jointsPosition_G';
S1 = 'P';
S2 = '.txt';
x = [S0 num2str(g) S1 num2str(p) S2];
Title = 'Position of Joint ';

A = importdata(x, '\t');

t = A(:,1);

figure

for i = 2 : 10,
	y = [Title num2str(i-1)];
	subplot(4,3,plot_order(i-1));
	plot(t, A(:,i), 'Color', 'b', 'LineWidth',2);
	title(y)
	xlabel('Time [s]')
	ylabel('Joint Position [rad]')
end

end

