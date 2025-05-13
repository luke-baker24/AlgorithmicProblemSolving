import java.io.IOException;
import java.util.Scanner;

public class AlmostUnionFind {
    public static SetNode[] idToNode;
    public static SetHolder[] baseSets;

    public static void main(String[] args) throws IOException {
        Scanner io = new Scanner(System.in);

        while (true) {
            try {
                int setSize = io.nextInt();
                int testCases = io.nextInt();

                baseSets = new SetHolder[setSize + 1];
                idToNode = new SetNode[setSize + 1];

                for (int i = 1; i <= setSize; i++) {
                    baseSets[i] = new SetHolder(i);
                    idToNode[i] = make_set(i);
                }

                for (int i = 0; i < testCases; i++) {
                    int operation = io.nextInt();

                    int val1 = io.nextInt();

                    //Query operation
                    if (operation == 1) {
                        int val2 = io.nextInt();

                        if (setsEqual(val1, val2)) continue;

                        union(val1, val2);
                    }

                    //Move operation
                    else if (operation == 2) {
                        int val2 = io.nextInt();

                        if (setsEqual(val1, val2)) continue;

                        move(val1, val2);
                    }

                    //Print operation
                    else {
                        SetHolder x = find(idToNode[val1].parent);

                        System.out.println(x.setSize + " " + x.sum);
                    }
                }
            }
            
            catch (Exception e) {
                break;
            }
        }

        io.close();
    }

    public static class SetNode {
        public int rank;
        public SetHolder parent;
        public int id;

        public SetNode(int rank, int id) {
            this.rank = rank;
            this.id = id;
            this.parent = baseSets[id];
        }
    }

    public static class SetHolder {
        public int id;

        public long sum;
        public int setSize;

        public int rank;
        public SetHolder parent;

        public SetHolder(int id) {
            this.id = id;

            this.sum = id;
            this.setSize = 1;

            this.rank = 0;
            this.parent = this;
        }
    }

    public static SetNode make_set(int x) {
        return new SetNode(0, x);
    }

    public static SetHolder find(SetHolder x) {
        if (x.parent != x) {
            x.parent = find(x.parent);
        }

        return x.parent;
    }

    public static boolean setsEqual(int x, int y) {
        return find(idToNode[x].parent) == find(idToNode[y].parent);
    }

    public static void union(int x, int y) {
        SetHolder nodeX = find(idToNode[x].parent);
        SetHolder nodeY = find(idToNode[y].parent);

        if (nodeX.rank > nodeY.rank) {
            nodeY.parent = nodeX;

            nodeX.sum += nodeY.sum;
            nodeX.setSize += nodeY.setSize;
        }
        else {
            nodeX.parent = nodeY;

            if (nodeX.rank == nodeY.rank)
                nodeY.rank++;

            nodeY.sum += nodeX.sum;
            nodeY.setSize += nodeX.setSize;
        }
    }

    public static void move(int x, int y) {
        //Pull nodeX from its set
        SetNode nodeX = idToNode[x];

        find(nodeX.parent).sum -= nodeX.id;
        find(nodeX.parent).setSize--;

        nodeX.parent = find(idToNode[y].parent);

        nodeX.parent.sum += nodeX.id;
        nodeX.parent.setSize++;
    }
}