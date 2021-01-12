/*

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

// helper function for internal use only
// transforms raw binary hash value into human-friendly hexademical form
void convert_hash(const unsigned char *str, char *output, int hash_length) {
  char append[16];
  strcpy (output, "");
  for (int n=0; n<hash_length; n++) {
    sprintf(append,"%02x",str[n]);
    strcat(output, append);
  }
}

// pre-supplied helper function
// generates the SHA1 hash of input string text into output parameter digest
// ********************** IMPORTANT **************************
// ---> remember to include -lcrypto in your linking step <---
// ---> so that the definition of the function SHA1 is    <---
// ---> included in your program                          <---
// ***********************************************************
void text_to_SHA1_digest(const char *text, char *digest) {
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1( (const unsigned char *) text, strlen(text), hash);
  convert_hash(hash, digest, SHA_DIGEST_LENGTH);
}

int leading_zeros(const char *digest) {
    bool starting_section = true;
    int lead_count = 0;
    while(*digest != '\0') {
        if(starting_section && *digest == '0') {
            lead_count++;
        }
        else if(*digest != '0') {
            starting_section = false;
        }
        if(!isxdigit(*digest)) {
            return -1;
        }
        digest++;
    }
    return lead_count;
}

bool file_to_SHA1_digest(const char *filename, char *digest) {
    ifstream file;
    file.open(filename);
    if(file.fail()) {
        digest = "error";
        return false;
    }
    char text[25000];
    char each;
    int i = 0;
    while(file.get(each)) {
        text[i] = each;
        i++;
    }
    file.close();
    text_to_SHA1_digest(text, digest);
    return true;
}

bool make_header(const char *recipient, const char *filename, char *header) {
    int attempts = 0;
    char file_digest[41], header_digest[41];
    if(!file_to_SHA1_digest(filename, file_digest)) {
        return false;
    }
    char counter[15];
    while(attempts < 10000000) {
        strcpy(header, "");
        strcpy(counter, "");

        strcat(header, recipient);
        strcat(header, ":");
        strcat(header, file_digest);
        strcat(header, ":");
        sprintf(counter, "%d", attempts);
        strcat(header, counter);

        text_to_SHA1_digest(header, header_digest);
        if(leading_zeros(header_digest) == 5) {
            return true;
        }
        attempts++;
    }
    return false;
}

MessageStatus check_header(const char *email_address, const char *header, const char *filename) {
    int colon_count = 0;
    char parsed_header[100], sent_email[50], sent_digest[41], sent_counter[15];
    strcpy(parsed_header, header);

    char* searched;
    searched = strtok(parsed_header, ":");

    char *aftersentemail = read_until_delim(parsed_header, sent_email);
    char *aftersentdigest = read_until_delim(aftersentemail, sent_digest);
    char *aftereverything = read_until_delim(aftersentdigest, sent_counter);

    if(strcmp(email_address, sent_email) != 0) {
        return WRONG_RECIPIENT;
    }

    char client_side_digest[41];
    file_to_SHA1_digest(filename, client_side_digest);
    if(strcmp(client_side_digest, sent_digest) != 0) {
        return INVALID_MESSAGE_DIGEST;
    }

    char header_digest[41];
    text_to_SHA1_digest(header, header_digest);
    if(leading_zeros(header_digest) != 5) {
        return INVALID_HEADER_DIGEST;
    }

    return VALID_EMAIL;
}