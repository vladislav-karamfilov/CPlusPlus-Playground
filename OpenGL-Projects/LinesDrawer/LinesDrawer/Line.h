#include "Point.h"
#include "Color.h"
#include "LineStyle.h"

namespace LinesDrawer
{
	struct Line
	{
	public:
		Point FirstPoint;
		Point LastPoint;
		Color CurrentColor;
		LineStyle Style;

		Line() : FirstPoint(Point()), LastPoint(Point()), CurrentColor(Color()), Style(LineStyle::NORMAL) {
		}

		Line(Point firstPoint, Point lastPoint, Color color, LineStyle style) {
			this->FirstPoint = firstPoint;
			this->LastPoint = lastPoint;
			this->CurrentColor = color;
			this->Style = style;
		}

		bool operator==(const Line& other) {
			return this->FirstPoint == other.FirstPoint &&
				this->LastPoint == other.LastPoint &&
				this->CurrentColor == other.CurrentColor &&
				this->Style == other.Style;
		}
	};
}
