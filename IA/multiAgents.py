# multiAgents.py
# --------------
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


from util import manhattanDistance
from game import Directions
import random, util, time

from game import Agent

INF = float("inf")

class RandomAgent(Agent):
    def getAction(self, gameState):
      legalMoves = gameState.getLegalActions(self.index)
      chosenMove = random.choice(legalMoves)
      return chosenMove

class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions(1)

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        # successorGameState = currentGameState.generateSuccessor(1,action)
        # newPos = successorGameState.getPacmanPosition()
        # newFood = successorGameState.getFood()
        # newGhostStates = successorGameState.getGhostStates()
        # newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
        
        "*** YOUR CODE HERE ***"
        pacmanPosition = currentGameState.getPacmanPosition()
        ghostPosition = currentGameState.getGhostPosition(1)
        if ghostPosition[1] > pacmanPosition[1] and action == 'South':
          return 5
        elif ghostPosition[1] < pacmanPosition[1] and action == 'North': 
          return 5
        elif ghostPosition[0] > pacmanPosition[0] and action == 'West':
          return 5
        elif ghostPosition[0] < pacmanPosition[0] and action == 'East':
          return 5
        else: 
          return 1

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return manhattanDistance(currentGameState.getPacmanPosition(),currentGameState.getGhostPosition(1))
    #return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """
    
    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.

          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game
        """
        "*** YOUR CODE HERE ***"
        return self.minimax(gameState, self.depth, self.index)[1]
      
    def minimax(self, gameState, depth, agentIndex):
      if depth == 0 or gameState.isWin() or gameState.isLose():
         return (self.evaluationFunction(gameState), )

      childNodes = [(gameState.generateSuccessor(agentIndex,action),action) for action in gameState.getLegalActions(agentIndex)]

      if agentIndex==0:
        maximizingPlayer = True
      else:
        maximizingPlayer = False

      if agentIndex == gameState.getNumAgents()-1:
        depth = depth-1
        agentIndex = 0
      else:
        agentIndex = agentIndex +1

      if maximizingPlayer:
        values = [((self.minimax(child[0], depth, agentIndex)[0]),child[1]) for child in childNodes]
        return max(values)

      else:
        values = [((self.minimax(child[0], depth, agentIndex)[0]),child[1]) for child in childNodes]
        return min(values)
        

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        return self.alphaBeta(gameState, self.depth, self.index, (-INF,), (INF,))[1]
        
    def alphaBeta(self, gameState, depth, agentIndex, alpha, beta):
      #time.sleep(1)
      if depth == 0 or gameState.isWin() or gameState.isLose():
         return (self.evaluationFunction(gameState),)

      if agentIndex==0:
        maximizingPlayer = True
      else:
        maximizingPlayer = False

      if agentIndex == gameState.getNumAgents()-1:
        newDepth = depth-1
        newAgentIndex = 0
      else:
        newAgentIndex = agentIndex +1
        newDepth = depth

      

      if maximizingPlayer:
        for action in gameState.getLegalActions(agentIndex):
          successorGameState = gameState.generateSuccessor(agentIndex,action) 
          crida = (self.alphaBeta(successorGameState, newDepth, newAgentIndex, alpha, beta),action)
          #print "MAX ",crida
          #print "alpha ",alpha
          #print "beta ",beta
          if crida[0][0] > alpha[0]:
            cridaTmp = crida[0][0],action
            alpha = cridaTmp
          if alpha[0] >= beta[0]:
            return alpha
        return alpha

      else:
        for action in gameState.getLegalActions(agentIndex):
          successorGameState = gameState.generateSuccessor(agentIndex,action) 
          crida = (self.alphaBeta(successorGameState, newDepth, newAgentIndex, alpha, beta),action)
          #print "MIN ",crida
          #print "alpha ",alpha
          #print "beta ",beta
          if crida[0][0] < beta[0]:
            cridaTmp = crida[0][0],action
            beta = cridaTmp
          if beta[0] <= alpha[0]:
            return beta
        return beta


class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        "*** YOUR CODE HERE ***"
        util.raiseNotDefined()

def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction
