<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
  <h1>Terminal Minesweeper</h1>
  
  <br>
  
  <div style="margin-bottom: 20px;">
    <h2>Description</h2>
    <p>This repository contains a command-line Minesweeper game implemented in C++. The game features customizable grid size and bomb percentage.</p>
  </div>

  <br>

  <div style="margin-bottom: 20px;">
    <h2>Key Features</h2>
    <ol>
      <li><strong>Customizable Grid Size:</strong> Players can specify the number of rows and columns for the game grid.</li>
      <li><strong>Adjustable Bomb Percentage:</strong> Users can set the percentage of bombs in the minefield.</li>
      <li><strong>Interactive Gameplay:</strong> Players can navigate the grid using keyboard controls <code>[WASD]</code> and <code>spacebar</code> and reveal cells to uncover bombs or clear the minefield.</li>
      <li><strong>Victory and Defeat Conditions:</strong> The game detects when players have successfully cleared the minefield or when they hit a bomb, ending the game appropriately.</li>
      <li><strong>Reset Functionality:</strong> Players can choose to reset the game to start again with the same or different settings by pressing <code>'r'</code> during gameplay or using command-line options.</li>
    </ol>
  </div>

  <br>

  <div style="margin-bottom: 20px;">
    <h2>Getting Started</h2>
    <ol>
      <li><strong>Clone the Repository:</strong> Clone the repository to your local machine using the following command:
        <pre>git clone (link unavailable)</pre>
      </li>
      <li><strong>Compile the Code:</strong> Compile the C++ code using your preferred compiler (e.g., g++, Visual Studio).
        <pre>g++ termsweeper.cpp -o termsweeper</pre>
      </li>
      <li><strong>Run the Game:</strong> Execute the compiled executable to start playing the Minesweeper game.
        <pre>./termsweeper</pre>
      </li>
    </ol>
  </div>

  <br>

  <table>
    <thead>
      <tr>
        <th>Key</th>
        <th>Description</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><kbd>w</kbd>,<kbd>a</kbd>,<kbd>s</kbd>,<kbd>d</kbd></td>
        <td>Move cursor around</td>
      </tr>
      <tr>
        <td><kbd>SPACE</kbd></td>
        <td>Open cell</td>
      </tr>
      <tr>
        <td><kbd>f</kbd></td>
        <td>Flag/unflag cell</td>
      </tr>
      <tr>
        <td><kbd>r</kbd></td>
        <td>Restart</td>
      </tr>
      <tr>
        <td><kbd>q</kbd></td>
        <td>Quit</td>
      </tr>
    </tbody>
  </table>

  <br>

  <div style="margin-bottom: 20px;">
    <h2>Customization Options</h2>
    <ul>
      <li>To adjust the grid size, use the <code>-r</code> (rows) and <code>-c</code> (columns) command-line options.
        <pre>./termsweeper -r 15 -c 20</pre>
      </li>
      <li>To change the bomb percentage, use the <code>-b</code> command-line option.
        <pre>./termsweeper -b 25</pre>
      </li>
    </ul>
  </div>

  <br>

  <div style="margin-bottom: 20px;">
    <h2>Contributions</h2>
    <p>Contributions to the Minesweeper game are welcome! Feel free to fork the repository, make changes, and submit pull requests.</p>
  </div>

  <br>

  <div style="margin-bottom: 20px;">
    <h2>License</h2>
        <p>This Minesweeper game is licensed under the <a href="(link unavailable)">MIT License</a>. See the LICENSE file for more details.</p>
  </div>

  <br>

  <div style="margin-bottom: 20px;">
    <h2>Author</h2>
    <p>-Patrick Miller-</p>
  </div>
</body>
</html>
