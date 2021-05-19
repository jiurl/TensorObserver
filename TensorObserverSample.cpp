#include <vector>
#include <string>
using namespace std;

#include "TensorObserver.h"
using namespace ob;

int main()
{
	//////////////////////////////////////////////////
	tensorview::MatrixViewParam matrix_param;
	matrix_param.intensity_display_cell_height = 20;
	matrix_param.intensity_display_cell_width = 20;
	matrix_param.intensity_display_cell_space = 1;
	matrix_param.val_to_intensity_min = 0;
	matrix_param.val_to_intensity_max = 5;
	matrix_param.numeric_display_cell_space = 5;
	matrix_param.num_digits_to_display = 2;
	matrix_param.numeric_display_cell_color = RGB(200, 200, 200);
	matrix_param.is_hide_demical_point_and_zero_before = false;
	matrix_param.rect_pen_width = 2;
	matrix_param.numeric_display_positive_color = RGB(0, 0, 0);
	matrix_param.numeric_display_negative_color = RGB(0, 255, 0);

	vector<unsigned int> background_colors;
	background_colors.push_back(RGB(221, 221, 221));
	background_colors.push_back(RGB(255, 221, 221));
	background_colors.push_back(RGB(217, 217, 243));

	tensorview::ChildTensorViewParam child_tensor_param;
	child_tensor_param.border_size = 10;
	child_tensor_param.space_size = 8;
	child_tensor_param.colors = background_colors;

	ObserverWndParam observer_wnd_param;
	observer_wnd_param.scroll_unit = 20;
	observer_wnd_param.left_space_in_document = 10;
	observer_wnd_param.top_space_in_document = 10;
	observer_wnd_param.record_space = 20;

	Param& param = getParam();
	param.matrix_param = matrix_param;
	param.child_tensor_param = child_tensor_param;
	param.observer_wnd_param = observer_wnd_param;

	//////////////////////////////////////////////////
	vector<float> v = { 1, 1, 1, 2, 2, 2, -5, 3, 3, 4, 4, 4, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4 };
	Tensor a = Tensor({ 2, 2, 2, 3 }, v.data());

	vector<string> infos = { "a", "b", "c", "d", "e" };

	ObserverWnd observer_wnd;

	{
		Record record;

		TensorView a_view = TensorView(&a, TensorDisplayType::NUMERIC);
		ColorRect rect(2, 0, 1, 2, RGB(255, 0, 0));
		a_view.AddRect(rect);
		record.Append(move(a_view), 10);

		TextView info = TextView(infos[0]);
		record.Append(info, 0);

		TextView hello = TextView("hello");
		record.AppendToLastTensor(move(hello), FollowType::RIGHT, 5);

		record.Append(TextView("test"), 10);

		observer_wnd.records.push_back(record);
	}

	// main thread will block here, until observer_wnd close or press enter key in observer_wnd.
	observer_wnd.Show(100, 100, 640, 480);

	for (int i = 0; i < 3; i++)
	{
		Record record;

		TensorView a_view = TensorView(&a);
		TextView info = TextView(infos[i]);

		info.Follow(a_view, FollowType::BOTTOM, 2);

		record.Add(a_view);
		record.Add(info);

		observer_wnd.records.push_back(record);
	}

	observer_wnd.Show(100, 100, 640, 480);

	observer_wnd.records.clear();
	for (int i = 0; i < 4; i++)
	{
		Record record;

		TensorView a_view = TensorView(&a);
		TextView info = TextView(infos[i]);

		info.Follow(a_view, FollowType::BOTTOM, 2);

		record.Add(a_view);
		record.Add(info);

		observer_wnd.records.push_back(record);
	}

	observer_wnd.Show(100, 100, 640, 480);

	printf("press ENTER to exit");
	getchar();

	return 0;
}