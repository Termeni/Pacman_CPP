from pacman import GameState
from layout import *
from multiAgents import *

def getMovement(layoutText, agentIndex, difficulty):
    
    gameState = GameState()
    
    numGhosts = layoutText.count('G')

    layoutText = layoutText.split('\n')
    layoutText = filter(None,layoutText)

    layout = Layout(layoutText)

    gameState.initialize(layout,numGhosts);
    
    if difficulty == 1:
        agent = ReflexAgent()
        agent.index = agentIndex
        direction = agent.getAction(gameState)
    elif difficulty == 2:
        agent = MinimaxAgent()
        agent.index = agentIndex
        direction = agent.getAction(gameState)
    elif difficulty == 3:
        agent = AlphaBetaAgent()
        agent.index = agentIndex
        agent.depth = 3
        direction = agent.getAction(gameState)
    else:
        agent = RandomAgent()
        agent.index = agentIndex
        direction = agent.getAction(gameState)

    if direction == 'North':
        return 1
    elif direction == 'South':
        return 2
    elif direction == 'West':
        return 3
    else:
        return 4
