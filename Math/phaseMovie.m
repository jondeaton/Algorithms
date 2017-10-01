function phaseMovie
%Displays Animated Phaes Plane Plots
%Jon Deaton 3/9/2015

    function f = funct(s,t)
        
        %=============== EDIT HERE ====================%
        % FUNCTION DEFINITION
        %s = complex argument
        %t = time (ranges 0 to 1 during animation)
        %f = function output
        
        f = exp(i*pi*t*s).*tan(t*s+4+2*exp(i*4*pi*t))+sin(i*t*s*exp(2*pi*i*t));

        % Some examples
        %f = tan(s).*sin(exp(i*3*pi*t)*(i*s));
        %f = sin(2*pi*i*s*t).*exp(22*pi*i*t);
        %f = ln(1*s*i+tan(i*s*exp(3*i*pi*t)))+exp(i*s-3*pi*t);
        %==============================================%
        
    end

%=============== EDIT HERE ===================%
% IMAGE PARAMETERS

animate = true; % If not animated, then t = 1

bounds = [-10, 10, -8, 8]; % Bounds of complex-plane segment

Neval = 1e5; % Number of function evaluations per image frame

h = 50; % Image adjustment parameter, higher = brighter image, range: (0, inf)

autoadjust = true; % If set to true, a suitable "h" will be calculated and used

blend = false; % Used for still imaged only, to smooth low definition images

magnification = 1; % Magnifies image by this factor

%=============================================%



clc; close all;
relo = bounds(1);
rehi = bounds(2);
imlo = bounds(3);
imhi = bounds(4);
if(animate)
    NFrames = 100;
else
    NFrames = 1;
end

%Creation of Real and Imaginary Axes for function evaluation
dimRatio = (rehi - relo)/(imhi - imlo);
realAx = linspace(relo,rehi,floor(sqrt(dimRatio*Neval)));
imagAx = linspace(imhi,imlo,floor(sqrt(Neval/dimRatio)));
[x,y] = meshgrid(realAx, imagAx);
s = x + i*y;

%Reference Image Creation
figure(1);
Z = funct(s,1/2);
if(sum(sum(~isfinite(Z))) > 0 )
    infLocs = ~isfinite(Z);
    Z(infLocs) = 0;
    fMax = max(max(abs(Z)));
    Z(infLocs) = fMax;
end

%Color Auto Adjustment
if(autoadjust)
    averageIntensity  = 0.5; %aproximate average intensity of image
    tol = 0.005;
    h = 1;
    im = complex2RGB(Z,h);
    avg = mean(mean(mean(im)));
    count = 0;
    while(abs(log(h)) < 10 && abs(avg - averageIntensity) > tol)
        h = h*(10).^(averageIntensity - avg);
        im = complex2RGB(Z,h);
        avg = mean(mean(mean(im)));
        count = count+1;
    end
end

fMax = max(max(abs(Z)));
bound = fMax / sqrt(2);
reRef = linspace(-bound,bound,floor(sqrt(Neval)));
imRef = linspace(bound,-bound,floor(sqrt(Neval)));
[xRef yRef] = meshgrid(reRef, imRef);
sRef = xRef + i*yRef;
reference = complex2RGB(sRef,h);
imshow(reference);
text(0.03*sqrt(Neval),(1-0.1)*sqrt(Neval),'Black: Zero');
text(0.03*sqrt(Neval),(1-0.05)*sqrt(Neval),...
    sprintf('White: Function Maximum ( %.2d)',max(max(abs(Z)))));
text(2,5,sprintf('Color  adjustment  factor: %.3f ',h));
fontsize = 14;
title('Color Reference','fontsize',fontsize)
xlabel('Real Axis','fontsize',fontsize);
ylabel('Imaginary Axis','fontsize',fontsize);


figure(2);
title('Function Output');
xlabel('Real Axis');
ylabel('Imaginary Axis');

while (true) %Animation continues until window is closed
    for n = 1:NFrames
        if(gcf ~= 2)
            break;
        end
        
        t = n/NFrames;
        tic;
        Z = funct(s,t);
        if(~animate)
            disp(sprintf('%.2f sec = function evaluation time', toc));
        end
        
        %Make sure that Z isn't a scalar
        if(size(Z) == 1)
            Z = ones(size(s))*funct(s,t);
        end
        
        %Make infinite values the maximum(white)
        if(sum(sum(~isfinite(Z))) > 0 )
            infLocs = ~isfinite(Z);
            Z(infLocs) = 0;
            fMax = max(max(abs(Z)));
            Z(infLocs) = fMax;
        end
        
        %Generation of RGB image
        phaseImage = complex2RGB(Z,h);
        if(blend && ~animate)
            tic;
            disp('Blending image...');
            phaseImage = blendIm(phaseImage);
            disp(sprintf('%.2f sec = blend time',toc));
        end
        imshow(phaseImage,'InitialMagnification',100*magnification);
        if(animate)
            text(0,5,sprintf('%.2f',t));
        end
        pause(0.00001);
    end
    if(gcf ~= 2 || ~animate)
        break;
    end
    
end


    function [rgbImage] = complex2RGB(A, h)
        %This function takes in matrix A of complex numbers and returns a
        %corresponding RGB M by N by 3 matrix
        %Black will always be zero, and white will be the function maximum.
        %
        %The parameter h is for color adjustment:
        %h = 1 is unadjusted
        %Larger h makes differences in magnitudes of mid-range complex numbers less
        %pronounced
        
        angles = angle(A);
        angles = mod(angles,2*pi);
        angles = angles*(180/pi);
        
        mags = abs(A);
        
        black = 0;
        white = max(max(mags));
        
        %For dealing with uniform magnitudes
        if(isUniform(mags))
            white = sqrt(2)*white;
        end
        
        %Color Adjustment (via h)
        saturation = ((white - mags)/(white - black)).^h;
        value = ((mags - black)/(white - black)).^(1/h);
        
        dims = size(angles);
        
        Red = zeros(dims);
        Green = zeros(dims);
        Blue = zeros(dims);
        
        rgbImage = zeros(dims(1),dims(2),3);
        
        low  = value.*(1-saturation);
        high = value;
        
        slope = (high - low)/60;
        
        region1 = find(angles <= 60);
        region2 = find((angles > 60) .* (angles <= 120));
        region3 = find((angles > 120) .* (angles <= 180));
        region4 = find((angles > 180) .* (angles <= 240));
        region5 = find((angles > 240) .* (angles <= 300));
        region6 = find((angles > 300) .* (angles <= 360));
        
        %0 to 60 degrees
        Red(region1) = high(region1);
        Green(region1) = low(region1) + slope(region1).*angles(region1);
        Blue(region1) = low(region1);
        
        %60 to 120 degrees
        Red(region2) = high(region2) - slope(region2).*(angles(region2) - 60);
        Green(region2) = high(region2);
        Blue(region2) = low(region2);
        
        %120 to 180 degrees
        Red(region3) = low(region3);
        Green(region3) = high(region3);
        Blue(region3) = low(region3) + slope(region3).*(angles(region3) - 120);
        
        %180 to 240 degrees
        Red(region4) = low(region4);
        Green(region4) = high(region4) - slope(region4).*(angles(region4) - 180);
        Blue(region4) = high(region4);
        
        %240 to 300 degrees
        Red(region5) = low(region5) + slope(region5).*(angles(region5) - 240);
        Green(region5) = low(region5);
        Blue(region5) = high(region5);
        
        %300 to 360 degrees
        Red(region6) = high(region6);
        Green(region6) = low(region6);
        Blue(region6) = high(region6) - slope(region6).*(angles(region6) - 300);
        
        rgbImage(:,:,1) = Red;
        rgbImage(:,:,2) = Green;
        rgbImage(:,:,3) = Blue;
        
        function uniform  = isUniform(X)
            
            uniform = 0 == sum(sum(X ~= X(1)));
            
        end
    end


end
