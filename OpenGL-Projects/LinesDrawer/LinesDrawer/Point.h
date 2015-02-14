namespace LinesDrawer
{
	struct Point
	{
	public:
		int X;
		int Y;

		Point() : X(0), Y(0) {
		}

		Point(int x, int y) {
			this->X = x;
			this->Y = y;
		}

		bool operator==(const Point& other) {
			return this->X == other.X && this->Y == other.Y;
		}
	};
}
