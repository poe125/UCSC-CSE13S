#include "names.h"
#include <stdio.h>
#include <stdlib.h>

int get_player_num() {
  int num_players = 3;
  printf("Number of players (3 to 10)?");
  int scanf_result = scanf("%d", &num_players);

  int result;

  // why do you need scanf_result < 1 when it is being covered with num_players
  // < 3?
  if (scanf_result < 1 || num_players < 3 || 10 < num_players) {
    result = 3;
    fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
  } else {
    result = num_players;
    printf("Selected number of players: %d\n", result);
  }
  return result;
}
int get_seed() {
  unsigned seed = 4823;
  printf("Random-number seed?");
  unsigned scanf_result = scanf("%u", &seed);
  if (scanf_result < 1) {
    fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
  }

  return seed;
}
int get_random(int SEED, int count) {
  // get random number for dice
  srandom(SEED);
  int num;
  for (int i = count; i > 0; i--) {
    num = (int)(random() / (double)RAND_MAX * 6) + 1;
  }
  // printf(" -generated %d\n", num);
  return num;
}

const char *get_player_name(int num_player) {
  return player_name[num_player - 1];
}

int start_game(int SEED, int num_player, int chip[], const char *player[]) {
  int dice;
  int i = 0;
  int no_chip;
  int winner;
  int play = 0;
  //   const char* current_player;
  do { // do the loop until there are no chips
    for (int j = 0; j < num_player; j++) { // 1 loop through all players
      play = 0;
      if (chip[j] > 0) { // do this only when there are chips
        // get a random dice number every time by adding 1 to i
        play = 1;
        for (int l = 0; l < chip[j]; l++) {
          dice = get_random(SEED, i);
          if (l == 0) {
            // name of the person rolling the dice
            printf("%s:", player[j]);
          }
          if (dice == 4) { // LEFT clockwise
            chip[j] -= 1;
            chip[(j + 1) % num_player] += 1;
            i++;
          } else if (dice == 5) { // CENTER
            chip[j] -= 1;
            i++;
          } else if (dice == 6) { // RIGHT counter clockwise
            chip[j] -= 1;
            chip[(j - 1 + num_player) % num_player] += 1;
            i++;
          } else {
            i++;
          }
        }
      } else {
        i++;
      }
      if (play == 1) {
        printf("ends her turn with %d\n", chip[j]);
      }
    }
    no_chip = 0;
    for (int k = 0; k < num_player; k++) {
      if (chip[k] < 1) {
        no_chip++;
      } else {
        winner = k;
      }
    }
  } while (no_chip != num_player - 1);
  return winner;
}

int main() {
  // get number of players and seed number by player input
  int num_players = get_player_num();
  unsigned SEED = get_seed();

  // set list of character names
  const char *player[num_players];
  printf("Names of the players playing:\n");
  for (int i = 0; i < num_players; i++) {
    player[i] = get_player_name(i + 1);
    printf("Player %d name: %s\n", i + 1, player[i]);
  }
  // set list of chip for each character
  int chip[num_players];
  for (int i = 0; i < num_players; i++) {
    chip[i] = 3;
  }

  typedef enum { DOT, LEFT, CENTER, RIGHT } Position;
  const Position die[6] = {DOT, DOT, DOT, LEFT, CENTER, RIGHT};

  int num_winner = start_game(SEED, num_players, chip, player);
  const char *winner = player[num_winner];
  printf("%s won!\n", winner);

  return 0;
}