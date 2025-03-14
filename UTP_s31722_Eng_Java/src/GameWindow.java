import Board.BoardView;

import javax.swing.*;
import java.awt.*;

public class GameWindow extends JFrame {
    public GameWindow() {
        //TODO redSlider, BlueSlider,GreenSlider to change the color of the pieses and of the board
        setMinimumSize(new Dimension(720,720));
        setLayout(new GridBagLayout());
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        getContentPane().setBackground(Color.black);
        add(new BoardView());


    }
}
