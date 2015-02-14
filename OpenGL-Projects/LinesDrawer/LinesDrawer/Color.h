namespace LinesDrawer {
	struct Color {
	public:
		double Red;
		double Green;
		double Blue;

		// Default color is white
		Color() : Red(1), Green(1), Blue(1) {
		}

		Color(double red, double green, double blue) {
			this->Red = red;
			this->Green = green;
			this->Blue = blue;
		}

		bool operator==(const Color& other) {
			return this->Red == other.Red && this->Green == other.Green && this->Blue == other.Blue;
		}
	};
}