#include <vector>
#include <iostream>
#include <map>

// defining a universe
// Each of the universes has these unique characteristics
// 1. active_player
// 2. active player rolled dice (in a turn it can be 0, 1, 2, 3?)
// 3. p1. score
// 4. p2. score
// 5. dice turn_sum

enum player_id {ID_1=1, ID_2=2};
enum ap_rolled {ROLLS_0=0, ROLLS_1=1, ROLLS_2=2, ROLLS_3 = 3};

struct Universe {
	player_id active_player;
	ap_rolled ap_rolled_dice; // active player rolled this may dice this turn
	int p1_position;
	int p2_position;
	int p1_score;
	int p2_score;
	int turn_sum; // this turn the active_player rolled this much points already
};

bool operator==(const Universe& u1, const Universe& u2) {
	return (
		u1.active_player == u2.active_player &&
		u1.ap_rolled_dice == u2.ap_rolled_dice &&
		u1.p1_position == u2.p1_position &&
		u1.p2_position == u2.p2_position &&
		u1.p1_score == u2.p1_score &&
		u1.p2_score == u2.p2_score &&
		u1.turn_sum == u2.turn_sum
		);
}
bool operator<(const Universe& u1, const Universe& u2) {
	if (u1.p1_score < u2.p1_score) return true;
	if (u1.p1_score > u2.p1_score) return false;
	if (u1.p1_position < u2.p1_position) return true;
	if (u1.p1_position > u2.p1_position) return false;
	if (u1.p2_position < u2.p2_position) return true;
	if (u1.p2_position > u2.p2_position) return false;
	if (u1.p2_score < u2.p2_score) return true;
	if (u1.p2_score > u2.p2_score) return false;
	if (u1.active_player < u2.active_player) return true;
	if (u1.active_player > u2.active_player) return false;
	if (u1.ap_rolled_dice < u2.ap_rolled_dice) return true;
	if (u1.ap_rolled_dice > u2.ap_rolled_dice) return false;
	return u1.turn_sum < u2.turn_sum;

}


int main() {

	// this will track universes
	std::map<Universe, long long> universes;

	// starting position
	universes[Universe{ ID_1, ROLLS_0, 5, 10, 0, 0, 0 }] = 1;
	long long p1_wins{ 0 };
	long long p2_wins{ 0 };

	// execute game
	while (universes.size() > 0) {

		// grab first
		Universe u = universes.begin()->first;
		long long u_num = universes.begin()->second;
		// erase first
		universes.erase(universes.begin());

		// execute game step for universe u
		// 1. active_player rolls a d3 - universe splits
		std::vector<Universe>new_universes;
		for (int r = 1; r <= 3; r++) new_universes.push_back(Universe{
			u.active_player, ap_rolled(int(u.ap_rolled_dice) + 1),
			u.p1_position, u.p2_position, u.p1_score, u.p2_score, u.turn_sum + r
			});
		// 2. check for turn_end for each new_universe
		for (Universe& nu : new_universes) {
			switch (nu.ap_rolled_dice) {
				// if active player rolled 3 dice, that player's turn ends
			case ROLLS_3: {
				// 2.1 active players turn ends, do different things depending on which player it is
				switch (nu.active_player) {
				case ID_1: {
					// 2.1.1 move player on the board by turn_sum
					nu.p1_position += nu.turn_sum;
					// 2.1.2 clear turn sum
					nu.turn_sum = 0;
					// 2.1.3 position wraps after 10 (board specific), since we're rolling d3, cannot wrap more than once
					if (nu.p1_position > 10) nu.p1_position -= 10;
					// 2.1.4 update score
					nu.p1_score += nu.p1_position;
					// 2.1.5 move to the other players turn
					nu.active_player = ID_2;
					nu.ap_rolled_dice = ROLLS_0;
					break;
				}
				case ID_2: {
					// 2.2.1 move player on the board by turn_sum
					nu.p2_position += nu.turn_sum;
					// 2.2.2 clear turn sum
					nu.turn_sum = 0;
					// 2.2.3 position wraps after 10 (board specific), since we're rolling d3, cannot wrap more than once
					if (nu.p2_position > 10) nu.p2_position -= 10;
					// 2.2.4 update score
					nu.p2_score += nu.p2_position;
					// 2.2.5 move to the other players turn
					nu.active_player = ID_1;
					nu.ap_rolled_dice = ROLLS_0;
					break;
				}
				default: {} // should not happen!
				}
				break;
			}
			default: {} // if rolls_0, rolls_1, rolls_2 - do nothing - turn in progress
			}
		}
		// 3. update the universes map, while checking for winners
		for (Universe& nu : new_universes) {
			if (nu.p1_score >= 21) p1_wins += u_num;
			else if (nu.p2_score >= 21) p2_wins += u_num;
			else {
				try { universes.at(nu) += u_num; }
				catch (std::out_of_range) { universes[nu] = u_num; }
			}
		}
		// loop ends, continue the game
		//std::cout << universes.size() << std::endl;
	}
	
	std::cout << "P1 wins: " << p1_wins << " times. P2 wins: " << p2_wins << " times. Most wins: " << std::max(p1_wins, p2_wins) << std::endl;

}