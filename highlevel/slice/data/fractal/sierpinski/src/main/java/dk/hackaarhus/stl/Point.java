package dk.hackaarhus.stl;

/**
 * Point represents a point in 3D space. This is not a value object, this is mutable
 * @author ermh
 */
public class Point {

    private double x, y, z;

    public Point() {
    }

    public Point(double xyz) {
        this(xyz, xyz, xyz);
    }

    public Point(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public Point(Point b1, Point b2) {
        setAvg(b1, b2);
    }

    public void set(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public final void setAvg(Point p1, Point p2) {
        this.x = (p1.x + p2.x) / 2d;
        this.y = (p1.y + p2.y) / 2d;
        this.z = (p1.z + p2.z) / 2d;
    }

    public void scale(double factor) {
        x *= factor;
        y *= factor;
        z *= factor;
    }

    public void set(Point other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    public void add(Point other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    public void sub(Point other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    public double dist(Point other) {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return Math.sqrt(dx * dx + dy * dy + dz * dz);
    }

    public double length() {
        return Math.sqrt(x * x + y * y + z * z);
    }

    @Override
    public String toString() {
        return "[" + x + "," + y + "," + z + "]";
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getZ() {
        return z;
    }
    
    

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Point other = (Point) obj;
        if (Double.doubleToLongBits(this.x) != Double.doubleToLongBits(other.x)) {
            return false;
        }
        if (Double.doubleToLongBits(this.y) != Double.doubleToLongBits(other.y)) {
            return false;
        }
        if (Double.doubleToLongBits(this.z) != Double.doubleToLongBits(other.z)) {
            return false;
        }
        return true;
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 83 * hash + (int) (Double.doubleToLongBits(this.x) ^ (Double.doubleToLongBits(this.x) >>> 32));
        hash = 83 * hash + (int) (Double.doubleToLongBits(this.y) ^ (Double.doubleToLongBits(this.y) >>> 32));
        hash = 83 * hash + (int) (Double.doubleToLongBits(this.z) ^ (Double.doubleToLongBits(this.z) >>> 32));
        return hash;
    }
}
