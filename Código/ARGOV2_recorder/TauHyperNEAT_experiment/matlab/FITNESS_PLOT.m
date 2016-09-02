function [y] = FITNESS_PLOT()
x = '../bin/simulation_files/fitness.txt';
y = '../bin/simulation_files/distance.txt';
z = '../bin/simulation_files/frecuency.txt';
fitness = importdata(x, '\t');
g = fitness(:,1);
m_fit= fitness(:,2);
dst_fit = fitness(:,3);

distance = importdata(y, '\t');
m_dis= distance(:,2);
dst_dis = distance(:,3);

frecuency = importdata(z, '\t');
m_fre= frecuency(:,2);
dst_fre = frecuency(:,3);

figure
hold on

plot(g, m_fit, 'Color', 'blue', 'DisplayName', 'Average fitness')
%plot(g, m_fit+dst_fit, 'LineStyle', '--', 'DisplayName', 'Standard desviation')
%plot(g, m_fit-dst_fit, 'LineStyle', '--')

plot(g, m_dis, 'Color', 'red', 'DisplayName', 'Average distance')
%plot(g, m_dis+dst_dis, 'LineStyle', '--', 'DisplayName', 'Standard desviation')
%plot(g, m_dis-dst_dis, 'LineStyle', '--')

plot(g, m_fre, 'Color', 'green', 'DisplayName', 'Average frecuency')
%plot(g, m_fre+dst_fre, 'LineStyle', '--', 'DisplayName', 'Standard desviation')
%plot(g, m_fre-dst_fre, 'LineStyle', '--')

xlabel('Generation')
ylabel('Fitness')
legend('show')
end

