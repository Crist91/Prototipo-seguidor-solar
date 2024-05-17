% Parámetros de entrada
latitud = 4.7;   % Latitud de Bogotá en grados Norte
dia_del_anio = 138; % Día del año
% Rango de horas solares locales (en horas)
horas = 0:0.5:24;
% Inicializar vectores para almacenar resultados
alturas = zeros(size(horas));
azimuts = zeros(size(horas));
% Cálculos para cada hora
for i = 1:length(horas)
    % Cálculo de la declinación solar
    declination = asind(0.39795 * cosd(0.98563 * (dia_del_anio - 173)));
    % Cálculo del ángulo horario
    angulo_horario = 15 * (horas(i) - 12);
    % Cálculo del argumento del arcoseno para la altura solar
    arg_asin = sind(latitud) * sind(declination) + cosd(latitud) * cosd(declination) * cosd(angulo_horario);
    % Corrección para el argumento del arcoseno
    if arg_asin > 1 
        arg_asin = 1;  % Limitar a 1 si es mayor
    elseif arg_asin < -1
        arg_asin = -1; % Limitar a -1 si es menor
    end
    % Cálculo de la altura solar
    alturas(i) = asind(arg_asin);
    % Cálculo del argumento del arcocoseno para el azimut solar
    if cosd(alturas(i)) ~= 0 
        arg_acos = (sind(declination) * cosd(latitud) - cosd(declination) * sind(latitud) * cosd(angulo_horario)) / cosd(alturas(i));
        % Corrección para el argumento del arcocoseno
        if arg_acos > 1
            arg_acos = 1;
        elseif arg_acos < -1
            arg_acos = -1;
        end
        % Cálculo del azimut solar
        azimuts(i) = acosd(arg_acos);
    else
        % Si la altura es 0, el azimut no está definido, se establece en 0 
        azimuts(i) = 0;
    end

    % Corrección para el azimut en la tarde
    if horas(i) > 12
        azimuts(i) = 360 - azimuts(i);
    end
end
% Gráfico de la trayectoria del sol (solo para valores válidos)
valid_idx = alturas >= 0; % Índices donde la altura es positiva (sobre el horizonte)
figure;
plot(horas(valid_idx), alturas(valid_idx));
hold on;
plot(horas(valid_idx), azimuts(valid_idx), 'r');
xlabel('Hora solar local (horas)');
ylabel('Ángulo (grados)');
title(['Posición del sol en Bogotá el día ', num2str(dia_del_anio)]);
legend('Altura solar', 'Azimut solar');
grid on;
