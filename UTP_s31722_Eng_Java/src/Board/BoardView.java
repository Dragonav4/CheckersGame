package Board;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class BoardView extends JPanel implements KeyListener {
    private IGameState gameState = new GameStateJNI();
    public static final int tileSize = 86;
    private static final Color beige = new Color(238,238,210);
    private static final Color green = new Color(118, 150, 86);
    private static final boolean allowViewFromOpponentSide = false;
    private int kbSelectedRow = -1;
    private int kbSelectedColumn = -1;

    public BoardView() {
        this.setBackground(Color.BLACK);
        this.setPreferredSize(new Dimension(gameState.getColumnsCount() * tileSize, gameState.getRowsCount() * tileSize));
        this.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 0));
        this.addKeyListener(this);
        setFocusable(true);
        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                var x = e.getX()/tileSize;
                var y = e.getY()/tileSize;

                if (!gameState.isActivePlayerWhite() && allowViewFromOpponentSide) {
                    x = gameState.getColumnsCount() - 1 - x;
                    y = gameState.getColumnsCount() - 1 - y;
                }

                gameState.handleClick(x,y);
                repaint();
                if (gameState.checkState() != 0) {
                    drawTheWinnerBanner();
                }
            }

        });

    }

    protected void drawTheWinnerBanner() {
        JDialog dialog = new JDialog((JFrame) SwingUtilities.getWindowAncestor(this), "GAME OVER", true);
        dialog.setSize(400, 250);
        dialog.setLocationRelativeTo(this);
        dialog.setLayout(new BorderLayout());
        dialog.setUndecorated(true); // убирает рамки для более чистого дизайна

        JPanel messagePanel = new JPanel();
        messagePanel.setLayout(new BorderLayout());
        messagePanel.setBackground(new Color(238, 238, 210));
        messagePanel.setBorder(BorderFactory.createLineBorder(new Color(70, 70, 70), 5, true));

        JLabel resultLabel;
        int gameStateResult = gameState.checkState();
        if (gameStateResult == 1) {
            resultLabel = new JLabel("Black WON!", SwingConstants.CENTER);
        } else if (gameStateResult == 2) {
            resultLabel = new JLabel("White WON!", SwingConstants.CENTER);
        } else {
            resultLabel = new JLabel("Draw or No Moves Left", SwingConstants.CENTER);
        }

        resultLabel.setFont(new Font("Arial", Font.BOLD, 28));
        resultLabel.setForeground(new Color(60, 63, 65));
        resultLabel.setOpaque(false);

        messagePanel.add(resultLabel, BorderLayout.CENTER);

        JButton resetButton = new JButton("RESET");
        resetButton.setFont(new Font("Arial", Font.PLAIN, 20));
        resetButton.setBackground(new Color(255, 99, 71));
        resetButton.setForeground(new Color(255, 99, 71));
        resetButton.setFocusPainted(false);
        resetButton.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20));
        resetButton.addActionListener(e -> dialog.dispose());

        resetButton.addActionListener(e -> {
            dialog.dispose();      // Закрытие окна диалога
            gameState.resetGame(); // Сброс состояния игры
            repaint();             // Перерисовка игрового поля
        });
        // Добавляем анимацию для плавного появления
        Timer timer = new Timer(10, new ActionListener() {
            float opacity = 0.0f;

            @Override
            public void actionPerformed(ActionEvent e) {
                opacity += 0.05f;
                dialog.setOpacity(Math.min(opacity, 1.0f));
                if (opacity >= 1.0f) {
                    ((Timer)e.getSource()).stop();
                }
            }
        });
        timer.start();

        dialog.add(messagePanel, BorderLayout.CENTER);
        dialog.add(resetButton, BorderLayout.SOUTH);

        dialog.setVisible(true);
        gameState.resetGame();
    }

    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2D = (Graphics2D) g;



        for (int r = 0; r < gameState.getRowsCount() ; r++) {
            for (int c = 0; c < gameState.getColumnsCount() ; c++) {
                g2D.setColor((c+r)%2 == 0 ? beige : green);
                g2D.fillRect(c * tileSize, r * tileSize, tileSize, tileSize);

                drawFigureOnPosition(g2D, c, r);
                if (c == kbSelectedColumn && r == kbSelectedRow) {
                    g2D.setColor(Color.red);
                    g2D.setStroke(new BasicStroke(3));
                    g2D.drawRect(c * tileSize+1, r * tileSize+1, tileSize-2, tileSize-2);
                }
            }
        }

    }



    private void drawFigureOnPosition(Graphics2D g2D, int c, int r) {
        var x = gameState.isActivePlayerWhite() || !allowViewFromOpponentSide
                ? c : gameState.getColumnsCount() - 1 - c;
        var y = gameState.isActivePlayerWhite() || !allowViewFromOpponentSide
                ? r : gameState.getRowsCount() - 1 - r;
        if (gameState.hasFigure(x,y)) {
            var isWhite = gameState.getFigureColor(x, y) == 'w';
            g2D.setColor(isWhite ? Color.ORANGE : Color.black);

            g2D.fillOval(tileSize*c+10, tileSize*r+10, tileSize-20, tileSize-20);
            if (gameState.isQueen(x, y)) {
                g2D.setColor(isWhite ? Color.black : Color.white);
                g2D.drawString("W",tileSize*c+tileSize/2-7, tileSize*r+tileSize/2-7);
            }
            if(gameState.mustAttack(x,y)) {
                g2D.setStroke(new BasicStroke(1));
                g2D.setColor(Color.red);
                g2D.drawOval(tileSize*c+10, tileSize*r+10, tileSize-20, tileSize-20);
            }
            if(gameState.isSelected(x, y)) {
                g2D.setStroke(new BasicStroke(3));
                g2D.setColor(Color.red);
                g2D.drawOval(tileSize*c+10, tileSize*r+10, tileSize-20, tileSize-20);
            }

        }
        else if (gameState.isValidMove(x, y)) {
            g2D.setColor(Color.magenta);
            g2D.fillRect(c * tileSize+tileSize/2-4, r * tileSize+tileSize/2-4, 8, 8);
        }

    }

    @Override
    public void keyTyped(KeyEvent e) {
    }

    private int normalizeX(int x){
        if (x<0) return 0;
        if (x>=gameState.getColumnsCount())
            return gameState.getColumnsCount()-1;
        return x;
    }

    private int normalizeY(int y){
        if (y<0) return 0;
        if (y>=gameState.getRowsCount())
            return gameState.getRowsCount()-1;
        return y;
    }
    @Override
    public void keyPressed(KeyEvent e) {



            switch (e.getKeyCode()) {
                case KeyEvent.VK_UP:
                    kbSelectedColumn = normalizeX(kbSelectedColumn);
                    kbSelectedRow = normalizeY(kbSelectedRow-1);
                    repaint();
                    break;
                case KeyEvent.VK_DOWN:
                    kbSelectedColumn = normalizeX(kbSelectedColumn);
                    kbSelectedRow = normalizeY(kbSelectedRow+1);
                    repaint();
                    break;
                case KeyEvent.VK_LEFT:
                    kbSelectedColumn = normalizeX(kbSelectedColumn-1);
                    kbSelectedRow = normalizeY(kbSelectedRow);
                    repaint();
                    break;
                case KeyEvent.VK_RIGHT:
                    kbSelectedColumn = normalizeX(kbSelectedColumn+1);
                    kbSelectedRow = normalizeY(kbSelectedRow);
                    repaint();
                    break;
                case KeyEvent.VK_SPACE:
                    gameState.handleClick(normalizeX(kbSelectedColumn), normalizeY(kbSelectedRow));
                    repaint();
                    break;
            }
        }

    @Override
    public void keyReleased(KeyEvent e) {

    }
}



