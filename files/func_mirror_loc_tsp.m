function[locations] = func_mirror_loc_tsp(point_map)

locations = zeros(length(point_map),2);
locations(:,1) = point_map(:,2);
locations(:,2) = point_map(:,1);

end