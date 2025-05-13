import java.io.IOException;

public class DisjointSetUnionFind {
    public static SetNode[] idToNode;

    public static void main(String[] args) throws IOException {
        FastIO io = new FastIO();

        int setSize = io.nextInt();
        int testCases = io.nextInt();

        idToNode = new SetNode[setSize];

        for (int i = 0; i < setSize; i++) {
            idToNode[i] = make_set(i);
        }

        for (int i = 0; i < testCases; i++) {
            char operation = io.nextWord().charAt(0);

            int val1 = io.nextInt();
            int val2 = io.nextInt();

            //Query operation
            if (operation == '?') {
                if (setsEqual(val1, val2)) io.println("yes");
                else io.println("no");
            }

            //Merge operation
            else {
                union(val1, val2);
            }
        }

        io.close();
    }

    public static class SetNode {
        public int rank;
        public SetNode parent;
        public int id;

        public SetNode(int rank, int id) {
            this.rank = rank;
            this.id = id;
            this.parent = this;
        }
    }

    public static SetNode make_set(int x) {
        return new SetNode(0, x);
    }

    public static SetNode find(SetNode x) {
        if (x.parent != x) {
            x.parent = find(x.parent);
        }

        return x.parent;
    }

    public static boolean setsEqual(int x, int y) {
        return find(idToNode[x]) == find(idToNode[y]);
    }

    public static void union(int x, int y) {
        SetNode nodeX = find(idToNode[x]);
        SetNode nodeY = find(idToNode[y]);

        if (nodeX.rank > nodeY.rank) {
            nodeY.parent = nodeX;
        }
        else {
            nodeX.parent = nodeY;

            if (nodeX.rank == nodeY.rank) nodeY.rank++;
        }
    }
}