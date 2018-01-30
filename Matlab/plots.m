p = plot(STOCHASTICdifcorrectmeanArray(:,1),STOCHASTICdifcorrectmeanArray(:,2),RNDNdif1Array(:,1),RNDNdif1Array(:,2));

% p(1).DisplayName='Stochastic';
% p(2).DisplayName='RNDN';

p(1).MarkerEdgeColor = 'b';
p(2).MarkerEdgeColor = 'g';

p(1).LineWidth = 1.5;
p(2).LineWidth = 1.5;

ax = gca;
ax.YScale = 'log';

xlabel('Floating point precision');
ylabel('Square deviation compared to optimal Lorenz Attractor run (prec=200)');

legend({'Stochastic rounding mode','Round to Nearest'})

title({'Deviation of RNDN rounding and Stochastic rounding compared to optimal';'Lorenz Attractor run (10^5 iterations) for various floating point precisions'}); 

p;
