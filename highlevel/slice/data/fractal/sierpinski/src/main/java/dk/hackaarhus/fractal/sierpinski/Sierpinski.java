package dk.hackaarhus.fractal.sierpinski;

import dk.hackaarhus.stl.Point;
import dk.hackaarhus.stl.StlWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.UnsupportedEncodingException;

/**
 * Generates a Sierpinski Tetrahedron to a given StlWriter
 */
public class Sierpinski {

    public static void generateFractal(int recursionDepth, double baseLength, File outputFile) throws UnsupportedEncodingException, FileNotFoundException {


        System.out.println("Creating Level " + recursionDepth + " Sierpinski Tetrahedron");
        System.out.println("\tBase Length " + baseLength);
        System.out.println("\tFile: " + outputFile.getAbsolutePath());

        StlWriter stl = new StlWriter(outputFile);
        Sierpinski sp = new Sierpinski(stl);
        sp.sierpinski(recursionDepth, baseLength);
        
        System.out.println("Done");
    }
    private final StlWriter stl;

    Sierpinski(StlWriter stl) {
        this.stl = stl;
    }

    public void sierpinski(int recursionDepth, double baseLength) {
        Point b1 = Tetra.b1;
        Point b2 = Tetra.b2;
        Point b3 = Tetra.b3;
        Point b4 = Tetra.b4;

        b1.scale(baseLength);
        b2.scale(baseLength);
        b3.scale(baseLength);
        b4.scale(baseLength);

        final String name = "sierpinski" + recursionDepth;
        stl.startSolid(name);

        sierpinski(recursionDepth, b1, b2, b3, b4);
        stl.endSolid(name);
        stl.close();
    }

    private void sierpinski(int depth, Point b1, Point b2, Point b3, Point b4) {

        if (depth > 0) {
            // subdivide
            Point b12 = between(b1, b2);
            Point b23 = between(b2, b3);
            Point b31 = between(b3, b1);

            Point b14 = between(b1, b4);
            Point b24 = between(b2, b4);
            Point b34 = between(b3, b4);

            sierpinski(depth - 1, b1, b12, b31, b14);  // lower corner 1
            sierpinski(depth - 1, b2, b23, b12, b24);  // lower corner 2
            sierpinski(depth - 1, b3, b31, b23, b34);  // lower corner 3
            sierpinski(depth - 1, b14, b24, b34, b4);  // upper tetraoide
        } else {
            // generate STL
            plane(b3, b2, b1);
            plane(b1, b2, b4);
            plane(b2, b3, b4);
            plane(b3, b1, b4);
        }
    }

    private Point between(Point b1, Point b2) {
        return new Point(b1, b2);
    }

    private static Point[] vector(int length) {
        Point v[] = new Point[length];
        for (int i = 0; i < length; i++) {
            v[i] = new Point();
        }
        return v;
    }

    private void plane(Point b1, Point b2, Point b3) {
        stl.facet(b1, b2, b3);
    }

    public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
        int min = 0;
        int max = 6;

        if (args.length == 0) {
            MainFrame config = new MainFrame();
            config.pack();
            config.setLocationByPlatform(true);
            config.setVisible(true);
        } else if (args.length >= 1) {
            min = max = Integer.parseInt(args[0]);
            for (int recursionDepth = min; recursionDepth <= max; recursionDepth++) {
                generateFractal(recursionDepth, 1, new File("sierpinski-" + recursionDepth + ".stl"));
            }
        }
    }

    /** 
     * The four points of a unit tetrahedron
     */
    public static class Tetra {

        /** bottom near left */
        public static Point b1 = new Point(0, 0, 0);
        /** bottom near right */
        public static Point b2 = new Point(1, 0, 0);
        /** bottom far center */
        public static Point b3 = new Point(0.5, Math.sqrt(3d / 4d), 0);
        /** top summit point */
        public static Point b4 = new Point(0.5, Math.sqrt(1d / 12d),
                Math.sqrt(2d / 3d));
    }
}
