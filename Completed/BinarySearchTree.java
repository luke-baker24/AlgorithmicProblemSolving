/**
 * Binary Search Tree implementation in Java.
 * Supports insertion, search, deletion, and in-order traversal.
 */
public class BinarySearchTree {

    /**
     * Node class representing each node in the BST.
     */
    private class Node {
        int value;
        Node left, right;

        Node(int value) {
            this.value = value;
        }

        /**
         * Inserts a value into the subtree rooted at this node.
         */
        void insert(int val) {
            if (val < value) {
                if (left == null) {
                    left = new Node(val);
                } else {
                    left.insert(val);
                }
            } else if (val > value) {
                if (right == null) {
                    right = new Node(val);
                } else {
                    right.insert(val);
                }
            }
        }

        /**
         * Searches for a value in the subtree rooted at this node.
         */
        boolean contains(int val) {
            if (val == value) return true;
            if (val < value) return left != null && left.contains(val);
            return right != null && right.contains(val);
        }

        /**
         * Returns the minimum value node in the subtree rooted at this node.
         */
        Node getMin() {
            return left == null ? this : left.getMin();
        }

        /**
         * Deletes a value from the subtree rooted at this node.
         * Returns the root of the modified subtree.
         */
        Node delete(int val) {
            if (val < value) {
                if (left != null) left = left.delete(val);
            } else if (val > value) {
                if (right != null) right = right.delete(val);
            } else {
                if (left == null) return right;
                if (right == null) return left;

                Node successor = right.getMin();
                value = successor.value;
                right = right.delete(successor.value);
            }
            return this;
        }

        /**
         * Performs an in-order traversal and appends values to the given StringBuilder.
         */
        void inOrder(StringBuilder result) {
            if (left != null) left.inOrder(result);
            result.append(value).append(" ");
            if (right != null) right.inOrder(result);
        }
    }

    private Node root;

    /**
     * Inserts a value into the BST.
     */
    public void insert(int val) {
        if (root == null) {
            root = new Node(val);
            return;
        }
        root.insert(val);
    }

    /**
     * Checks whether a value exists in the BST.
     */
    public boolean contains(int val) {
        return root != null && root.contains(val);
    }

    /**
     * Deletes a value from the BST.
     */
    public void delete(int val) {
        if (root != null) root = root.delete(val);
    }

    /**
     * Returns a string representing the in-order traversal of the BST.
     */
    public String inOrderTraversal() {
        StringBuilder result = new StringBuilder();
        if (root != null) root.inOrder(result);
        return result.toString().trim();
    }
}
