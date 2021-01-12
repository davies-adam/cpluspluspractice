enum MessageStatus {
  INVALID_HEADER=-1,
  WRONG_RECIPIENT=-2,
  INVALID_MESSAGE_DIGEST=-3,
  INVALID_HEADER_DIGEST=-4,
  VALID_EMAIL=1
};

/* pre-supplied helper function */
/* generates the SHA1 hash of input string text into output parameter digest */
void text_to_SHA1_digest(const char *text, char *digest);

// checks SHA1 in hexademical format if it contains only valid numerals and returns num of leading zeroes
int leading_zeros(const char *digest);

// reads file and puts SHA1 digest in already allocated char array. returns false if not read.
bool file_to_SHA1_digest(const char *filename, char *digest);

// converts information for formatted header to send. returns false if wasn't able to create.
bool make_header(const char *recipient, const char *filename, char *header);

// helper function for splitting c-strings
char* read_until_delim(char *base, char *result, char delim = ':');

// checks to see if header is correctly formatted.
MessageStatus check_header(const char *email_address, const char *header, const char *filename);
