# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util
import copy


class SearchNode:
    """
    This class represents a node in the graph which represents the search problem.
    The class is used as a basic wrapper for search methods - you may use it, however
    you can solve the assignment without it.

    REMINDER: You need to fill in the backtrack function in this class!
    """

    def __init__(self, position, parent=None, transition=None, cost=0, heuristic=0):
        """
        Basic constructor which copies the values. Remember, you can access all the
        values of a python object simply by referencing them - there is no need for
        a getter method.
        """
        self.position = position
        self.parent = parent
        self.cost = cost
        self.heuristic = heuristic
        self.transition = transition

    def isRootNode(self):
        """
        Check if the node has a parent.
        returns True in case it does, False otherwise
        """
        return self.parent == None

    def unpack(self):
        """
        Return all relevant values for the current node.
        Returns position, parent node, cost, heuristic value
        """
        return self.position, self.parent, self.cost, self.heuristic

    def backtrack(self):
        """
        Reconstruct a path to the initial state from the current node.
        Bear in mind that usually you will reconstruct the path from the
        final node to the initial.
        """
        moves = []
        # make a deep copy to stop any referencing isues.
        node = copy.deepcopy(self)

        if node.isRootNode():
            # The initial state is the final state
            return moves

        "**YOUR CODE HERE**"
        util.raiseNotDefined()


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        return (self.startingPosition, self.corners)

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return [s, s, w, s, w, w, s, w]


def generalGraphSearch(problem, structure):
    """
    generalni algoritam za pretrazivanje grafa, prima strukturu koja treba imati svojstva da je moguce
    izvrsavati .pop() i .push() i kao drugi parametar prima problem
    """

    # [(state, action, cost)] oblik podatka koji se pusha u strukturu koja je predana kao argument funkcije
    structure.push([(problem.getStartState(), "Stop", 0)])

    # lista posjecenih stanja
    visited = []

    # petlja koja traje sve dok postoji podataka u strukturi
    while not structure.isEmpty():

        # fronta stanja koja cekaju na ekspanziju
        frontier = structure.pop()
        # trenutno stanje je zadnji podatak u strukturi
        curr_state = frontier[len(frontier) - 1]
        # stanje u podatku se nalazi na prvom mjestu
        curr_state = curr_state[0]

        # provjera je li trenutno stanje ciljno stanje
        if problem.isGoalState(curr_state):
            # vraca se staza(niz akcija) od pocetnog stanja do ciljnog izuzev pocetnog
            return [x[1] for x in frontier][1:]

        if curr_state not in visited:
            # tek ako trenutno stanje nije u posjecenim, tek onda ga dodajemo
            visited.append(curr_state)
            # petlja za svu djecu trenutnog stanja
            for successor in problem.getSuccessors(curr_state):
                # ako djeca stanja nisu posjecena ili generirana negdje prije dodaju se u stazu
                if successor[0] not in visited:
                    # pomocna lista koja sadrzi stazu
                    succPath = frontier[:]
                    # dodajemo dijete stazi
                    succPath.append(successor)
                    # pomocna staza s novim clanom se stavlja u strukturu
                    structure.push(succPath)
    return False


def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState(problem.getStartState())
    print "Start's successors:", problem.getSuccessors(problem.getStartState())
    """
    # kao struktura u algoritmu se koristi stog
    return generalGraphSearch(problem, util.Stack())


def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    # kao struktura u algoritmu se koristi red
    return generalGraphSearch(problem, util.Queue())


def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    # kod ovog algoritma potrebno je i uracunati trosak puta za sve osim prvog stanja
    cost = lambda path: problem.getCostOfActions([x[1] for x in path][1:])
    return generalGraphSearch(problem, util.PriorityQueueWithFunction(cost))


def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0


def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    # funkcija troska se sastoji od g(x) i h(x); g(x) - trosak to trenutnog stanja, h(x) - heuristiska
    # funkcija koja procijenjuje trosak do ciljnog stanja; nikad ne precjenjuje
    # path[-1][0] oznacava zadnje stanje u strukturi
    cost = lambda path: problem.getCostOfActions([x[1] for x in path][1:]) + heuristic(path[-1][0], problem)
    return generalGraphSearch(problem, util.PriorityQueueWithFunction(cost))


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
