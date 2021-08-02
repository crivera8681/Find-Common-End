#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

struct vector3d
{
	float x;
	float y;
	float z;
};

typedef vector3d point3d;

float get_distance_between_two_points(point3d pt_0, point3d pt_1);
vector<point3d> get_all_end_points(point3d start_point, float length);
vector<point3d> find_common_endpoints(point3d p0, point3d p1, float length_0, float length_1);
bool intersect_line_segments(point3d point_0, float length_0, point3d point_1, float length_1, vector3d hint_direction, point3d &out_common_endpoint);

int main()
{
	point3d common_endpoint;
	bool results = false;
	results = intersect_line_segments({ 0,0,0 }, 2.0, { 2,0,0 }, 2.0, { 1,0,1 }, common_endpoint);

	cout << "Result: " << endl;
	if (results == true)
	{
		cout << "Common Endpoint: { " << common_endpoint.x << ", " << common_endpoint.y << ", " << common_endpoint.z << " }" << endl;
	}
	else
	{
		cout << "There are no common endpoints.\n";
	}

	return 0;
}

bool intersect_line_segments(point3d point_0, float length_0, point3d point_1, float length_1, vector3d hint_direction, point3d &out_common_endpoint)
{
	float distance = 0;
	float smallest_dist = 1000000000000000000000000000000000.0;
	int index = 0;
	vector<point3d> common_endpoints = find_common_endpoints(point_0, point_1, length_0, length_1);

	if (common_endpoints.size() > 0)
	{
		for (int i = 0; i < int(common_endpoints.size()); i++)
		{
			distance = get_distance_between_two_points(common_endpoints[i], { hint_direction.x, hint_direction.y, hint_direction.z });

			if (distance < smallest_dist)
			{
				index = i;
			}
		}

		out_common_endpoint = common_endpoints[index];
		return true;
	}
	else
	{
		return false;
	}
}

float get_distance_between_two_points(point3d pt_0, point3d pt_1)
{
	float out_distance;

	out_distance = ((pt_1.x - pt_0.x) * (pt_1.x - pt_0.x)) + ((pt_1.y - pt_0.y) * (pt_1.y - pt_0.y)) + ((pt_1.z - pt_0.z) * (pt_1.z - pt_0.z));

	out_distance = sqrt(out_distance);

	return out_distance;
}

vector<point3d> get_all_end_points(point3d start_point, float length)
{
	vector<point3d> end_points;
	point3d endpoint;
	float theta_0;
	float theta_1;

	for (int i = 0; i < 360; i++)
	{
		theta_0 = (i / .01745329);
		for (int x = 0; x < 360; x++)
		{
			theta_1 = (x / .01745329);
			endpoint.x = start_point.x + length * cos(theta_0) * cos(theta_1);
			endpoint.y = start_point.y + length * sin(theta_0) * cos(theta_1);
			endpoint.z = start_point.z + length * sin(theta_1);
			end_points.push_back(endpoint);
		}
	}

	return end_points;
}  

vector<point3d> find_common_endpoints(point3d p0, point3d p1, float length_0, float length_1)
{
	vector<point3d> points_0;
	vector<point3d> points_1;
	vector<point3d> common_endpoints;
	float comparator_x;
	float comparator_y;
	float comparator_z;
	points_0 = get_all_end_points(p0, length_0);
	points_1 = get_all_end_points(p1, length_1);

	for (int i = 0; i < int(points_0.size()); i++)
	{
		p0 = points_0[i];
		cout << i << endl;
		for (int q = 0; q < int(points_1.size()); q++)
		{
			p1 = points_1[q];

			comparator_x = abs((p0.x - p1.x));
			if (comparator_x <= .01)
			{
				comparator_y = abs((p0.y - p1.y));
				if (comparator_y <= .01)
				{
					comparator_z = abs((p0.z - p1.z));
					if (comparator_z <= .01)
					{
						common_endpoints.push_back(p0);
					}
				}
			}
		}
	}

	return common_endpoints;
}