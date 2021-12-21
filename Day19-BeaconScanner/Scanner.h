#include <vector>

// forward declaration instead of include
struct Beacon;

enum Rotation { is_x, is_y, is_z };

struct Scanner
{
public:
	Scanner(const std::vector<Beacon>& b) : beacons{ b } {}
	Scanner() {}

	void set_position(int x, int y, int z) { x_pos = x;	y_pos = y;	z_pos = z; }
	void set_orientation(int xo, int yo, int zo) { x_o = xo; y_o = yo;	z_o = zo; }
	void set_rotation(Rotation xr, Rotation yr, Rotation zr) { x_r = xr; y_r = yr, z_r = zr; }

	int x() const { return x_pos; }
	int y() const { return y_pos; }
	int z() const { return z_pos; }

	int xo() const { return x_o; }
	int yo() const { return y_o; }
	int zo() const { return z_o; }

	Rotation x_r{ is_x };
	Rotation y_r{ is_y };
	Rotation z_r{ is_z };

	int get_id() const { return id; }
	void set_id(int i) { id = i; }

	int num_beacons() const { return beacons.size(); }
	void add_beacon(const Beacon& b) { beacons.push_back(b); }

	void attempt_allignment(Scanner& s);
	void mark_solved();

	void print() const;

//private:
	// will be  solved if position and orientation are correct 
	bool solved{ false };

	// 'absolute' position
	int x_pos{ 0 };
	int y_pos{ 0 };
	int z_pos{ 0 };

	// orientation, 1 // -1;
	int x_o{ 1 };
	int y_o{ 1 };
	int z_o{ 1 };

	// scanned beacons;
	std::vector<Beacon> beacons;

	// other
	int id{ 0 };
};

std::istream& operator>>(std::istream& is, Scanner& s);