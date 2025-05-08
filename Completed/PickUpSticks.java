import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.Stack;
import java.io.IOException;

public class PickUpSticks {
    public static void main(String[] args) throws IOException {
        FastIO io = new FastIO();

        int sticks = io.nextInt();
        int lines = io.nextInt();

        HashMap<Integer, GraphNode> graph = new HashMap<Integer, GraphNode>();

        for (int i = 0; i < sticks; i++) {
            graph.put(i, new GraphNode(i));

            graph.get(i).outgoingEdges = new HashSet<GraphNode>();
            graph.get(i).incomingEdges = new HashSet<GraphNode>();
        }

        boolean[] isNotTopNode = new boolean[sticks];

        for (int i = 0; i < lines; i++) {
            int fromId = io.nextInt() - 1;
            int toId = io.nextInt() - 1;

            GraphNode from = graph.get(fromId);
            GraphNode to = graph.get(toId);

            from.outgoingEdges.add(to);
            to.incomingEdges.add(from);

            isNotTopNode[toId] = true;
        }

        //Pop all sources off and work it down till there are only sinks. A source node indicates a highest stick.
        Stack<GraphNode> sources = new Stack<GraphNode>();

        for (int i = 0; i < sticks; i++) {
            if (!isNotTopNode[i]) sources.push(graph.get(i));
        }

        int sticksHandled = 0;
        ArrayList<Integer> output = new ArrayList<Integer>();
        while (!sources.isEmpty()) {
            GraphNode source = sources.pop();

            output.add(source.value + 1);

            sticksHandled++;

            for (GraphNode outgoing : source.outgoingEdges) {
                outgoing.incomingEdges.remove(source);

                if (outgoing.incomingEdges.isEmpty()) sources.add(outgoing);
            }
        }
        
        if (sticksHandled < sticks) io.println("IMPOSSIBLE"); 
        else 
            for (int i = 0; i < output.size(); i++)
                io.println(output.get(i));

        io.close();
    }

    public static class GraphNode {
        public int value;

        public Set<GraphNode> outgoingEdges;
        public Set<GraphNode> incomingEdges;

        public GraphNode(int value) {
            this.value = value;
        }
    }
}
