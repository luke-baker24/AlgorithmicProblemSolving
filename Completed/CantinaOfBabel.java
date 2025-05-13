import java.io.IOException;
import java.util.HashSet;
import java.util.Map.Entry;
import java.util.HashMap;
import java.util.Set;
import java.util.Stack;
import java.util.Scanner;

public class CantinaOfBabel {
    public static void main(String[] args) throws IOException {
        //For each character to handle, connect each language in its language list.
        //Then, find the largest strongly connected component. Then just subtract that from graph size.

        Scanner io = new Scanner(System.in);

        int characters = io.nextInt();
        io.nextLine();

        HashMap<String, GraphNode> graph = new HashMap<String, GraphNode>();
        HashMap<String, GraphNode> charactersLanguages = new HashMap<String, GraphNode>();

        for (int i = 0; i < characters; i++) {
            String line = io.nextLine();

            String[] lineBreakdown = line.split(" ");

            String characterName = lineBreakdown[0];
            String nativeLanguage = lineBreakdown[1];

            Set<String> languageSet = new HashSet<String>();

            for (int j = 1; j < lineBreakdown.length; j++)
                languageSet.add(lineBreakdown[j]);

            //Create a graph node for any newly discovered languages
            for (String lang : languageSet) {
                if (!graph.containsKey(lang)) {
                    graph.put(lang, new GraphNode(lang));
                    graph.get(lang).understandableLangs = new HashSet<GraphNode>();
                }
            }

            //For every language our character can understand, create a connection between the character's native language and it
            for (String otherLang : languageSet) {
                graph.get(nativeLanguage).understandableLangs.add(graph.get(otherLang));
            }

            charactersLanguages.put(characterName, graph.get(nativeLanguage));
        }

        //Find the strongly connected components
        for (Entry<String, GraphNode> node : graph.entrySet()) {
            if (!node.getValue().visited) Tarjan(node.getValue());
        }
        
        //Find the maximal strongly connected component of languages
        int minBaddies = Integer.MAX_VALUE;
        for (Set<GraphNode> component : stronglyConnectedComponents) {
            int baddies = 0;

            for (Entry<String, GraphNode> character : charactersLanguages.entrySet()) {
                if (!component.contains(character.getValue())) baddies++;
            }

            if (baddies < minBaddies) { 
                minBaddies = baddies;
            }
        }

        System.out.println(minBaddies);

        io.close();
    }

    static Set<Set<GraphNode>> stronglyConnectedComponents = new HashSet<Set<GraphNode>>();
    static int index = 0;
    static Stack<GraphNode> tarjanStack = new Stack<GraphNode>();

    public static void Tarjan(GraphNode node) {
        node.index = index;
        node.lowlink = index;

        index++;
        
        tarjanStack.push(node);

        node.onStack = true;
        node.visited = true;

        for (GraphNode neighborNode : node.understandableLangs) {
            if (!neighborNode.visited) {
                Tarjan(neighborNode);

                node.lowlink = Math.min(node.lowlink, neighborNode.lowlink);
            }
            else if (neighborNode.onStack) {
                node.lowlink = Math.min(node.lowlink, neighborNode.index);
            }
        }

        if (node.lowlink == node.index) {
            Set<GraphNode> stronglyConnectedComponent = new HashSet<GraphNode>();

            while (true && !tarjanStack.empty()) {
                GraphNode w = tarjanStack.pop();
                w.onStack = false;
                stronglyConnectedComponent.add(w);

                if (w == node) break;
            }

            stronglyConnectedComponents.add(stronglyConnectedComponent);
        }
    }

    public static class GraphNode {
        public String value;

        public Set<GraphNode> understandableLangs;

        public int index;
        public int lowlink;

        public boolean onStack;
        public boolean visited;

        public GraphNode(String value) {
            this.value = value;

            index = 0;
            lowlink = 0;

            onStack = false;
            visited = false;
        }

        public String toString() {
            return this.value;
        }
    }
}
