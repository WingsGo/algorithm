import curses
import random
import numpy as np
from enum import Enum
from collections import defaultdict


class GameField:
    actions = Enum('actions', ('Up', 'Down', 'Left', 'Right', 'Restart', 'Exit'))
    valid_actions = [action for action in actions]
    vaild_low_input = [ord(ch) for ch in 'wsadrq']
    vaild_upper_input = [ord(ch) for ch in 'WSADRQ']
    user_input_mapping = dict(zip(vaild_low_input, actions))
    user_input_mapping.update(dict(zip(vaild_upper_input, actions)))

    def __init__(self, rows=4, cols=4, win_score=2048):
        self.rows = rows
        self.cols = cols
        self.field = np.zeros((self.rows, self.cols), dtype=np.uint8)
        self.win_score = win_score
        self.high_score = 0
        self.current_score = 0
        self.reset()

    def spawn(self):
        random_num = 2 if random.randrange(100)>50 else 4
        (i, j) = random.choice([(i, j) for i in range(self.rows) for j in range(self.cols)
                                if self.field[i, j] == 0])
        self.field[i, j] = random_num

    def transpose(self, array):
        return [list(row) for row in zip(*array)]

    def reverse(self, array):
        return [row[::-1] for row in array]

    def reset(self):
        self.field = np.zeros((self.rows, self.cols), dtype=np.uint8)
        self.current_score = 0
        self.spawn()
        self.spawn()

    def move(self, order):
        assert isinstance(order, GameField.actions)

        def move_row_left(row):

            def tighten(row):
                new_row = [elem for elem in row if elem != 0]
                new_row += [0 for i in range(len(row) - len(new_row))]
                return new_row

            def merge(row):
                paire = False
                new_row = []
                for i in range(len(row)):
                    if paire:
                        new_row.append(2 * row[i])
                        self.current_score += 2 * row[i]
                        paire = False
                    else:
                        if i + 1 < len(row) and row[i] == row[i + 1]:
                            paire = True
                            new_row.append(0)
                        else:
                            new_row.append(row[i])
                return new_row

            return tighten(merge(tighten(row)))

        move_state = {}
        move_state[GameField.actions.Left] = lambda field: [move_row_left(row) for row in field]
        move_state[GameField.actions.Right] = lambda field: self.reverse(move_state[GameField.actions.Left](self.reverse(field)))
        move_state[GameField.actions.Up] = lambda field: self.transpose(move_state[GameField.actions.Left](self.transpose(field)))
        move_state[GameField.actions.Down] = lambda field: self.transpose(move_state[GameField.actions.Right](self.transpose(field)))

        if order in move_state:
            if self.is_move_able(order):
                self.field = np.array(move_state[order](self.field))
                self.spawn()
                return True
            else:
                return False

    def is_move_able(self, direction):
        def is_move_left_able(field):
            def is_row_move_able(row):
                def change(i):
                    if row[i] == 0 and row[i + 1] != 0:
                        return True
                    if row[i] != 0 and row[i + 1] == row[i]:
                        return True
                    return False

                return any(change(i) for i in range(len(row) - 1))
            return any(is_row_move_able(row) for row in field)

        move_able = {}
        move_able[GameField.actions.Left] = lambda field: is_move_left_able(field)
        move_able[GameField.actions.Right] = lambda field: move_able[GameField.actions.Left](self.reverse(field))
        move_able[GameField.actions.Up] = lambda field: move_able[GameField.actions.Left](self.transpose(field))
        move_able[GameField.actions.Down] = lambda field: move_able[GameField.actions.Right](self.transpose(field))

        if direction in move_able:
            return move_able[direction](self.field)
        else:
            return False

    def is_win(self):
        return True if self.field.max() >= self.win_score else False

    def is_gameover(self):
        return  not any(self.is_move_able(action) for action in self.actions)

    def draw(self, screen):
        help_string1 = '(W)Up (S)Down (A)Left (D)Right'
        help_string2 = '    (R)Restart (Q)Exit'
        gameover_string = '         GAME OVER'
        win_string = '      YOU WIN!'

        def cast(string):
            screen.addstr(string + '\n')

        # seperator for horizontal tile sqaures
        def draw_hor_separator():
            line = '+' + ('+------' * self.field.shape[0] + '+')[1:]
            separator = defaultdict(lambda: line)
            if not hasattr(draw_hor_separator, "counter"):
                draw_hor_separator.counter = 0
            cast(separator[draw_hor_separator.counter])
            draw_hor_separator.counter += 1

        # draws rows to create table to play game
        def draw_row(row):
            cast(''.join('|{: ^5} '.format(num) if num > 0 else '|      ' for
                         num in row) + '|')

        screen.clear()
        cast('SCORE: ' + str(self.current_score))
        if 0 != self.high_score:
            cast('HGHSCORE: ' + str(self.high_score))
        for row in self.field:
            draw_hor_separator()
            draw_row(row)
        draw_hor_separator()
        if self.is_win():  # if you win print you win string
            cast(win_string)
        else:
            if self.is_gameover():  # if you lose print game over string
                cast(gameover_string)
            else:
                cast(help_string1)
        cast(help_string2)

    @classmethod
    def get_user_action(cls, keyboard):
        char = 'N'
        while not char in cls.vaild_low_input + cls.vaild_upper_input:
            char = keyboard.getch()
        return cls.user_input_mapping[char]


class FSM:
    def __init__(self):
        self.init_stdscr()
        self.game_field = GameField()
        self.game_state = Enum('GameState',('Init', 'Game', 'GameWin', 'GameOver', 'Exit'))
        self.action_state = {
            self.game_state.Init: self.init_game,
            self.game_state.Game: self.on_game,
            self.game_state.GameWin: lambda :self.out_game(self.game_state.Win),
            self.game_state.GameOver: lambda :self.out_game(self.game_state.GameOver)
        }

    def init_stdscr(self):
        self.stdscr = curses.initscr()
        curses.noecho()
        curses.cbreak()
        self.stdscr.keypad(True)

    def init_game(self):
        #绘制界面,生成随机数
        self.game_field.reset()
        return self.game_state.Game

    def on_game(self):
        self.game_field.draw(self.stdscr)
        action = GameField.get_user_action(self.stdscr)
        if action == GameField.actions.Restart:
            return self.game_state.Init
        elif action == GameField.actions.Exit:
            return self.game_state.Exit
        elif self.game_field.move(action):
            if self.game_field.is_win():
                return self.game_state.GameWin
            elif self.game_field.is_gameover():
                return self.game_state.GameOver
            else:
                return self.game_state.Game
        else:
            return self.game_state.Game

    def out_game(self, state):
        assert isinstance(state, self.game_state)

        self.game_field.draw(self.stdscr)
        action = GameField.get_user_action(self.stdscr)
        response = defaultdict(lambda :state)
        response[GameField.actions.Restart], response[GameField.actions.Exit] = self.game_state.Init, self.game_state.Exit
        return response[action]

    def run(self):
        state = self.init_game()
        while state != self.game_state.Exit:
            state = self.action_state[state]()

fsm_2048 = FSM()
fsm_2048.run()
