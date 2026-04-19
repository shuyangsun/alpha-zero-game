# Guan Dan Rules

This document outlines rules for the popular Chinese cards game Guan Dan (掼蛋).

## Scope

- This is the 4-player partnership form of GuanDan.
- Seats are fixed in clockwise order `0 -> 1 -> 2 -> 3`.
- Teams are fixed as players `0` and `2` versus players `1` and `3`.
- This reference models normal in-hand play. Tribute and return-tribute are
  treated as pre-hand setup unless a later design explicitly adds a separate
  pre-hand phase.

## Cards and Card Identity

- GuanDan uses two standard 54-card decks, for a total of 108 physical cards.
- Suit matters. The exact rank and suit of a played card matter for rule
  evaluation, especially for wild cards and straight flushes.
- Only the heart of the acting player's team level rank is wild in this
  design. Because there are two decks, there can be at most two such wild
  cards in the hand.

## Teams and Levels

- Each team carries its own current level rank across hands.
- The two teams' levels may differ at the start of a hand.
- All players should optimize for team scores instead of individual scores at
  all times.
- Rank comparison is level-aware. The current level rank is promoted above the
  ordinary non-joker ranks for comparison purposes, so comparison logic must
  use effective rank rather than raw face value.
- The game starts with level 0 for both teams, with number `2` as the highest
  non-joker rank. Then the highest rank progresses to `3`, `4`, etc., all the
  way to ace.

## Turn Order and Trick Flow

- Play proceeds clockwise and skips any player who has already emptied their
  hand.
- A fresh trick has no benchmark. The leader of a fresh trick must play a legal
  non-pass combination.
- Once a player makes a non-pass declaration, that declared combination becomes
  the current benchmark that later players must beat.
- A later active player may either beat the current benchmark with a legal
  declaration or pass.
- Pass only applies within the current trick. Once every other still-active
  player has passed, the current benchmark holder wins the trick, all pass
  state is cleared, and that same player leads the next fresh trick.
- Because pass state resets at every fresh trick, pass is transient trick state
  rather than long-lived game state.

## Combination Families

- The implementation must distinguish these combination families:
  `pass`, `single`, `pair`, `triple`, `full house`, `straight`, `tube`,
  `plate`, `straight flush`, `bomb`, and `joker bomb`.
- `tube` means three consecutive pairs.
- `plate` means two consecutive triples.
- `straight` and `straight flush` must contain exactly 5 consecutive ranks.
- Comparison uses a declared key rank whose meaning depends on the family:
  - single, pair, triple, and ordinary bomb use the declared repeated rank.
  - Full house uses the rank of the triple component.
  - Straight and straight flush use the highest numerical number in the run
    (not rank). For example, if the current team level is 0, and the highest
    rank is `2`, the hand `2, 3, 4, 5, 6` has highest rank `6`, not `2`.
  - Tube uses the highest pair rank in the run.
  - Plate uses the highest triple rank in the run.
  - Joker bomb is its own special family, the highest rank possible in the game.
- Variable-length families still care about size. A straight only competes with
  a straight of the same length. The same principle applies to other
  sequence-based families. Ordinary bombs also compare by both size and rank.
- The maximum ordinary bomb size in this ruleset is 10 cards: eight natural
  cards of one rank plus both heart wild cards. This is rare, but it is legal.

## Wild Cards and Declaration Ambiguity

- Heart level cards may substitute for other cards inside legal combinations.
- The same physical set of cards can sometimes support more than one legal
  declaration.
- This ambiguity is strategically real, not just a notation issue. GuanDan is
  a partnership game, so deliberately declaring the same cards as a lower or
  different valid combination can be beneficial if it allows a partner to win
  the trick later.
- Once a player declares how the cards are being used, that declaration is
  binding for the trick. Later players must beat the declared interpretation,
  not merely the raw multiset of cards.
- As a result, a move in GuanDan is defined by both the exact cards played and
  the declared combination they represent.

## Beating Rules Relevant to State Tracking

- Ordinary follow-up play is not determined by cards alone. It depends on the
  declared family, the declared key rank interpreted under the acting team's
  level, and the size or shape of the declaration where that matters.
- Special high-power families such as straight flush, ordinary bomb, and joker
  bomb must remain distinct families in the rules model. Their exact
  cross-family beating order should be implemented explicitly and kept
  consistent with the chosen GuanDan house rules.
- The benchmark for the current trick is always the most recent non-pass
  declaration, not the most recent action overall.

## Finishing Order and Hand Result

- A player who empties their hand immediately leaves the turn rotation for the
  rest of the hand.
- The order in which players finish matters. It is not enough to know only
  which team eventually wins the hand.
- The design discussion assumes the standard team result categories:
  teammates finishing first and second is a triple-up result.
  Teammates finishing first and third is a double-up result.
  Teammates finishing first and fourth is a single-up result.
- Because finished players stop acting but their finish positions still matter
  for both rotation and scoring, the hand state must preserve finish order
  until the hand result is determined.

## Tribute Assumption

- Tribute and return-tribute depend on the previous hand's finishing order and
  affect the next hand's starting hands.
- This design assumes tribute is resolved before the first ordinary turn of the
  hand, typically while constructing the initial state for that hand.
- Tribute is therefore not part of the normal trick-play action space in the
  current design.
- If a later implementation wants the returning player to choose which card to
  give back, treat that as an explicit pre-hand phase rather than folding it
  into ordinary trick-play combinations.
