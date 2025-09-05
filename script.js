// --- Global Variables & State ---
let game; // This will hold our single C++ Game instance
let playerSymbol = 'X';
let aiSymbol = 'O';
let currentPlayer;
let gameIsOver = false;

// --- HTML Element Selectors ---
const symbolSelectionDiv = document.getElementById('symbol-selection');
const boardDiv = document.getElementById('board');
const statusDisplay = document.getElementById('status');
const restartButton = document.getElementById('restartButton');
const squares = document.querySelectorAll('.square');

// =====================================================================
// --- Game Logic Functions
// =====================================================================

/**
 * Kicks off a new game after a symbol has been chosen.
 */
function startGame() {
  // --- UI SETUP ---
  symbolSelectionDiv.classList.add('hidden');
  boardDiv.classList.remove('hidden');
  statusDisplay.classList.remove('hidden');

  game.reset(); // Reset the C++ board to empty
  gameIsOver = false;
  currentPlayer = 'X'; // X always starts the game

  // --- INITIAL DRAW ---
  updateBoard();
  statusDisplay.textContent = `Player ${currentPlayer}'s turn`;

  // --- AI's FIRST MOVE (if needed) ---
  if (currentPlayer === aiSymbol) {
    setTimeout(makeAIMove, 500); 
  }
}

/**
 * Gets the board state from C++ and draws it on the HTML grid.
 */
function updateBoard() {
  const boardState = game.getBoardState();
  squares.forEach((square, index) => {
    const symbol = boardState[index];

    // Set the text content
    square.textContent = (symbol === '_') ? '' : symbol;
    
    // Remove old classes and add the new one for coloring
    square.classList.remove('x-symbol', 'o-symbol');
    if (symbol === 'X') {
      square.classList.add('x-symbol');
    } else if (symbol === 'O') {
      square.classList.add('o-symbol');
    }
  });
}

/**
 * Handles the logic when the human player clicks a square.
 */
function handlePlayerMove(index) {
  // Do nothing if the game is over or if it's not the player's turn
  if (gameIsOver || currentPlayer !== playerSymbol) {
    return;
  }

  const position = index + 1; // C++ expects positions 1-9
  const moveWasValid = game.makeMove(playerSymbol, position);

  if (moveWasValid) {
    updateBoard();
    const isGameOver = checkGameState(); // Check if the player's move ended the game
    
    // If the game isn't over, it's the AI's turn
    if (!isGameOver) {
      currentPlayer = aiSymbol;
      statusDisplay.textContent = "AI is thinking...";
      setTimeout(makeAIMove, 700);
    }
  }
}

/**
 * Calls the C++ engine to find and make the AI's best move.
 */
function makeAIMove() {
  if (gameIsOver) return;

  // 1. Ask our C++ engine for the best move!
  const bestMove = game.findBestMove(); // Returns an object like { first: row, second: col }
  const row = bestMove.first;
  const col = bestMove.second;

  // 2. Convert coordinates to a 1-9 position
  const position = row * 3 + col + 1;

  // 3. Make the move in the C++ engine
  game.makeMove(aiSymbol, position);

  // 4. Update the game state
  updateBoard();
  const isGameOver = checkGameState();

  if (!isGameOver) {
    currentPlayer = playerSymbol; // Switch turn back to the player
    statusDisplay.textContent = `Player ${currentPlayer}'s turn`;
  }
}

/**
 * Checks if the game has ended (win, loss, or draw) and updates the UI.
 * @returns {boolean} - True if the game is over, false otherwise.
 */
function checkGameState() {
  const winnerCode = game.checkWinner();
  const winner = String.fromCharCode(winnerCode);

  if (winner !== '_') {
    gameIsOver = true;
    if (winner === 'D') {
      statusDisplay.textContent = "It's a draw!";
    } else {
      statusDisplay.textContent = `Player ${winner} wins!`;
    }
    restartButton.classList.remove('hidden');
    return true; // Game is over
  }
  return false; // Game is not over
}

/**
 * Resets the UI back to the initial symbol selection screen.
 */
function resetToSymbolChoice() {
  symbolSelectionDiv.classList.remove('hidden');
  boardDiv.classList.add('hidden');
  statusDisplay.classList.add('hidden');
  restartButton.classList.add('hidden');
  game.reset();
  updateBoard();
  // --- GAME STATE RESET ---
  playerSymbol = 'X';
  aiSymbol = 'O';
}

// =====================================================================
// --- Emscripten Module Setup ---
// =====================================================================

var Module = {
  onRuntimeInitialized: function() {
    console.log('Wasm is ready. Initializing game engine.');
    game = new Module.Game(); // Create the single C++ Game instance

    // --- Initial Event Listeners ---

    // Setup for the initial symbol choice buttons
    document.getElementById('choose-X').addEventListener('click', () => {
      playerSymbol = 'X';
      aiSymbol = 'O';
      startGame();
    });

    document.getElementById('choose-O').addEventListener('click', () => {
      playerSymbol = 'O';
      aiSymbol = 'X';
      startGame();
    });
    
    // Setup for the game board squares
    squares.forEach((square, index) => {
      square.addEventListener('click', () => handlePlayerMove(index));
    });

    // Setup for the restart button
    restartButton.addEventListener('click', resetToSymbolChoice);

    // Initial UI state
    resetToSymbolChoice();
    symbolSelectionDiv.classList.remove('hidden');
  }
};