enum ScoreModifier { NONE, DOUBLE_LETTER_SCORE, TRIPLE_LETTER_SCORE, DOUBLE_WORD_SCORE, TRIPLE_WORD_SCORE };

int tile_score(char tile);
bool can_form_word_from_tiles(const char *word, const char *tiles, char *played_tiles);
int compute_score(const char *played_tiles, ScoreModifier *modifiers);
int highest_scoring_word_from_tiles(const char *tiles, ScoreModifier *score_modifiers, char *word);

