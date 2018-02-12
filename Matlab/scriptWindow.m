
function scriptWindow(plot) 

figh = plot; % the handle of the newly created figure

if isunix()
    set(figh, 'Units', 'pixels');
    posn = get(figh, 'Position');

    % This attempts to work around the Matlab bug where an exception is
    % throw when exporting graphics if the figure window is not on the
    % primary monitor. The exception is:
    %
    % java.lang.IllegalArgumentException: adding a container to a container on a different GraphicsDevice
    %   at java.awt.Component.checkGD(Unknown Source)
    % 	at java.awt.Container.addImpl(Unknown Source)
    % 	at java.awt.Container.add(Unknown Source)
    % 	at com.mathworks.hg.peer.FigurePanel.doAdd(FigurePanel.java:215)
    % 	at com.mathworks.hg.peer.FigurePanel.assembleFigurePanel(FigurePanel.java:203)
    % 	at com.mathworks.hg.peer.FigurePanel.reconstructFigurePanel(FigurePanel.java:131)
    % 	at com.mathworks.hg.peer.FigurePanel.handleNotification(FigurePanel.java:88)
    %   ... [trimmed]
    %
    % The workaround is to identify the "primary monitor" according to
    % Java AWT, and then place the figure on that monitor.

    % Find the primary monitor
    screens = java.awt.GraphicsEnvironment.getLocalGraphicsEnvironment().getScreenDevices();
    primary = screens(1); % assume primary monitor is first in the array
    bounds = primary.getDefaultConfiguration().getBounds();

    % bounds is a java.awt.Rectangle object
    x = bounds.x;
    y = bounds.y;
    width = bounds.width;
    height = bounds.height;

    % Center the figure on this same window
    posn(1:2) = [(x + width/2 - posn(3)/2), (y + height/2 - posn(4)/2)];
    set(figh, 'Position', posn);
end
