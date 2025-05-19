import java.util.*;

public class ColonyPlanning {

    static class Point implements Comparable<Point> {
        int x, y;

        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public int compareTo(Point other) {
            if (this.y != other.y)
                return this.y - other.y;
            return this.x - other.x;
        }

        @Override
        public boolean equals(Object obj) {
            if (!(obj instanceof Point)) 
                return false;
            Point p = (Point) obj;
            return this.x == p.x && this.y == p.y;
        }
    }

    /**
     * we compute the cross product of vectors OA and OB:
     *    + if O to A to B is a left turn / ccw
     *    – if right turn
     *    0 if collinear
     */
    static long crossProduct(Point O, Point A, Point B) {
        long dxA = A.x - O.x;
        long dyA = A.y - O.y;
        long dxB = B.x - O.x;
        long dyB = B.y - O.y;
        return dxA * dyB - dyA * dxB;
    }

    // this is a custom comparator  to sort points by polar angle around a given pivot:

    // points that make a left turn come before right turns
    // if collinear, the closer one to the pivot comes first, but wil change this as Luke modifies his problem
    static class PolarAngleComparator implements Comparator<Point> {
        private final Point pivot;

        PolarAngleComparator(Point pivot) {
            this.pivot = pivot;
        }

        @Override
        public int compare(Point a, Point b) {
            long cross = crossProduct(pivot, a, b);
            // uf a is to the left of b around pivot -> a comes first
            if (cross > 0) 
                return -1;

            // if a is to the right of b -> b comes first
            else if (cross < 0) 
                return 1; 
            
            else {
                // Collinear: compare squared distances to pivot, cheesed from gfg with slight modficaitons
                long da = (long)(pivot.x - a.x)*(pivot.x - a.x)
                        + (long)(pivot.y - a.y)*(pivot.y - a.y);
                long db = (long)(pivot.x - b.x)*(pivot.x - b.x)
                        + (long)(pivot.y - b.y)*(pivot.y - b.y);
                return Long.compare(da, db);
            }
        }
    }

   // found smth really cool call Andrew's Monotonic chain, cite: gfg coming in handy again, but its still pretty modified
    static List<Point> computeConvexHull(List<Point> points) {
        int n = points.size();
        if (n < 3)
            return Collections.emptyList();

        // first we sort points lex in increasing x, then y, i think luke caught thsi in class too hehe
        points.sort((a, b) -> {
            if (a.x != b.x) return a.x - b.x;
            return a.y - b.y;
        });

        // then we build the lower half of the hull
        List<Point> lower = new ArrayList<>();
        for (Point p : points) {
            // pop only on a right turn - collinear (cross == 0) now stay
            while (lower.size() >= 2
                && crossProduct(lower.get(lower.size()-2),
                                lower.get(lower.size()-1),
                                p) < 0) {
                lower.remove(lower.size() - 1);
            }
            lower.add(p);
        }

        // next, build the upper half of the hull
        List<Point> upper = new ArrayList<>();
        for (int i = points.size() - 1; i >= 0; i--) {
            Point p = points.get(i);
            while (upper.size() >= 2
                && crossProduct(upper.get(upper.size()-2),
                                upper.get(upper.size()-1),
                                p) < 0) {
                upper.remove(upper.size() - 1);
            }
            upper.add(p);
        }

        // finally stitch lower and upper together (minus the duplicate endpoints)
        lower.remove(lower.size() - 1);
        upper.remove(upper.size() - 1);
        lower.addAll(upper);

        // at this point 'lower' is the full hull in CCW order, including all collinear boundary points
        return lower;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int totalPoints = scanner.nextInt();

        //simply ingest points
        List<Point> remaining = new ArrayList<>();
        for (int i = 0; i < totalPoints; i++) {
            int x = scanner.nextInt();
            int y = scanner.nextInt();
            remaining.add(new Point(x, y));
        }
        
        // vscode irritating, close scanner
        scanner.close();


        //  if the same site appears twice, it’s invalid immediately
        Set<Point> seen = new HashSet<>();
        for (Point p : remaining) {
            if (!seen.add(p)) {
                System.out.println("invalid");
               return;
            }
        }


        int loopCount = 0;
        Integer previousHullSize = null; // setting it integer helps with null check

        // keep peeling if points are >=3
        while (true) {
            List<Point> hull = computeConvexHull(remaining);
            int hullSize = hull.size();
            if (hullSize < 3) {
                // Cannot form another loop
                break;
            }

            // Enforce strictly decreasing sizes
            if (previousHullSize != null && hullSize > previousHullSize) {
                System.out.println("invalid");
                return;
            }

            loopCount++;
            previousHullSize = hullSize;

            //these are allthe points that our convex hull contains, returned by the graham scan helper
            Set<Point> hullSet = new HashSet<>(hull); // so we initialize it using hull
            List<Point> nextRemaining = new ArrayList<>(); //these are the reamining points

            for (Point p : remaining) {
                if (!hullSet.contains(p)) {
                    nextRemaining.add(p);
                }
            }
            remaining = nextRemaining;
        }
        //here we have less than 3 points remaining (<=2)

        //after peeling, exactly two points must remain (armory + cantina) and they must be distinct
        if (loopCount >= 1 
            && remaining.size() == 2 
            && !remaining.get(0).equals(remaining.get(1))) {
            System.out.println("valid " + loopCount);
        } else {
            System.out.println("invalid");
        }
    }
}