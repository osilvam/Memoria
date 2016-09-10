function [y] = CHAMPION_PLOT()
x = '../bin/simulation_files/champions.txt';
A = importdata(x, '\t');
g = A(:,1);
f = A(:,3);

figure
hold on

plot(g, f, 'LineWidth',2, 'DisplayName', 'Average frecuency');
xlabel('Generation');
ylabel('Fitness');
legend('show');

end