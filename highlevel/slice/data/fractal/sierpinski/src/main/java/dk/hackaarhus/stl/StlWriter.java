package dk.hackaarhus.stl;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

/**
 * Based on the description in wikipedia
 * @see http://en.wikipedia.org/wiki/STL_(file_format)
 */
public class StlWriter {

    private final PrintWriter out;
    
    public StlWriter(File fout) throws FileNotFoundException, UnsupportedEncodingException {
        this(new PrintWriter(fout, "UTF-8"));
    }

    public StlWriter(PrintWriter out) {
        this.out = out;
    }

    public void startSolid(String name) {
        out.print("solid ");
        out.println(name);
    }

    public void endSolid(String name) {
        out.print("endsolid ");
        out.println(name);
    }

    /**
     * Does not support normal vectors at the moment. It uses 0 vector instead, 
     * so be careful to order p1,p2,p3 according to the right hand rule.
     * @param p1
     * @param p2
     * @param p3 
     */
    public void facet(Point p1, Point p2, Point p3) {
        // facet normal ni nj nk
        out.println("facet normal 0 0 0");
        //   outer loop
        out.println(" outer loop");

        //     vertex v1x v1y v1z
        vertex(p1);
        //     vertex v2x v2y v2z
        vertex(p2);
        //     vertex v3x v3y v3z
        vertex(p3);

        //   endloop
        out.println(" endloop");
        // endfacet
        out.println("endfacet");

    }

    public void vertex(Point v) {
        // vertex v1x v1y v1z
        out.print("  vertex ");
        out.print(v.getX());
        out.print(" ");
        out.print(v.getY());
        out.print(" ");
        out.println(v.getZ());
    }

    public void close() {
        out.close();
    }

    // facet normal ni nj nk
    //   outer loop
    //     vertex v1x v1y v1z
    //     vertex v2x v2y v2z
    //     vertex v3x v3y v3z
    //   endloop
    // endfacet
}
