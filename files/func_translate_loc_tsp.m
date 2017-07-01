function[locations] = func_translate_loc_tsp(point_map,X,Y)
    points = length(point_map);
    
    locations = zeros(points,2);
    locations(:,1) = point_map(:,1) + X;
    locations(:,2) = point_map(:,2) + Y;
    %for p = 1:points
    %    locations(p,1) = point_map(p,1)+X;
    %    locations(p,2) = point_map(p,2)+Y;
    %end
end