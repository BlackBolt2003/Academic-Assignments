class NetworkNode:
    def __init__(self, name):
        self.name = name
        self.routing_table = {}

    def update_routing_table(self, destination, cost):
        self.routing_table[destination] = cost

    def get_routing_table(self):
        return self.routing_table


class LinkStateRouting:
    def __init__(self):
        self.nodes = {}

    def add_node(self, node):
        self.nodes[node.name] = node

    def update_link(self, source, destination, cost):
        if source in self.nodes and destination in self.nodes:
            self.nodes[source].update_routing_table(destination, cost)
            self.nodes[destination].update_routing_table(source, cost)

    def dijkstra(self, source):
        distance = {}
        unvisited = list(self.nodes.keys())
        for node in unvisited:
            distance[node] = float('inf')
        distance[source] = 0

        while unvisited:
            current_node = min(unvisited, key=lambda node: distance[node])
            unvisited.remove(current_node)

            for neighbor, cost in self.nodes[current_node].get_routing_table().items():
                if distance[current_node] + cost < distance[neighbor]:
                    distance[neighbor] = distance[current_node] + cost

        return distance

    def find_shortest_path(self, source, destination):
        distance = self.dijkstra(source)
        if distance[destination] == float('inf'):
            return "No path found"
        path = [destination]
        while destination != source:
            for neighbor, cost in self.nodes[destination].get_routing_table().items():
                if distance[destination] - cost == distance[neighbor]:
                    path.append(neighbor)
                    destination = neighbor
                    break
        path.reverse()
        return path


class DistanceVectorRouting:
    def __init__(self):
        self.nodes = {}

    def add_node(self, node):
        self.nodes[node.name] = node

    def update_routing_table(self):
        updated = True
        while updated:
            updated = False
            for node_name, node in self.nodes.items():
                for destination, cost in node.get_routing_table().items():
                    if node_name == destination:
                        continue
                    alternative_cost = node.get_routing_table()[node_name] + cost
                    if destination not in self.nodes[node_name].get_routing_table() or alternative_cost < self.nodes[node_name].get_routing_table()[destination]:
                        self.nodes[node_name].update_routing_table(destination, alternative_cost)
                        updated = True

    def find_shortest_path(self, source, destination):
        if source not in self.nodes or destination not in self.nodes:
            return "Invalid source or destination"
        if destination not in self.nodes[source].get_routing_table():
            return "No path found"
        path = [destination]
        while destination != source:
            for neighbor, cost in self.nodes[source].get_routing_table().items():
                if neighbor == destination:
                    path.append(source)
                    destination = source
                    break
        path.reverse()
        return path


# Example usage:

# Create nodes
A = NetworkNode("A")
B = NetworkNode("B")
C = NetworkNode("C")
D = NetworkNode("D")

# Initialize routing algorithms
link_state = LinkStateRouting()
distance_vector = DistanceVectorRouting()

# Add nodes to the algorithms
link_state.add_node(A)
link_state.add_node(B)
link_state.add_node(C)
link_state.add_node(D)

distance_vector.add_node(A)
distance_vector.add_node(B)
distance_vector.add_node(C)
distance_vector.add_node(D)

# Update links for link-state routing
link_state.update_link("A", "B", 1)
link_state.update_link("B", "C", 2)
link_state.update_link("C", "D", 1)
link_state.update_link("A", "D", 3)

# Update routing tables for distance-vector routing
A.update_routing_table("A", 0)
A.update_routing_table("B", 1)
A.update_routing_table("C", float('inf'))
A.update_routing_table("D", 3)

B.update_routing_table("A", 1)
B.update_routing_table("B", 0)
B.update_routing_table("C", 2)
B.update_routing_table("D", float('inf'))

C.update_routing_table("A", float('inf'))
C.update_routing_table("B", 2)
C.update_routing_table("C", 0)
C.update_routing_table("D", 1)

D.update_routing_table("A", 3)
D.update_routing_table("B", float('inf'))
D.update_routing_table("C", 1)
D.update_routing_table("D", 0)

# Calculate and print shortest paths
print("Link-State Routing Shortest Path from A to D:", link_state.find_shortest_path("A", "D"))
print("Distance-Vector Routing Shortest Path from A to D:", distance_vector.find_shortest_path("A", "D"))
