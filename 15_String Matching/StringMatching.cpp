#include <iostream>
#include <vector>

/*txt = text
# pat = pattern
# T = partial match table
# if all is True, report all matches; otherwise report first match only*/

vector<int> kmpFind(string txt, string pat, vector<int> T, bool all) {
	// start comparisons at beginning of text and pattern
	int m = 0;
	int i = 0;

	vector<int> matches; //list of matches to return

	while (m + i < txt.length()) {		//loop to end of text
		//characters match
		if (pat[i] == txt[m+i]) {
			//end of pattern
			if (i == pat.length()-1) {
				matches.push_back(m);

				if (!all) return matches;

				//move forward to search for more matches
				m = m + i - T[i];
				i = T[i];
            }

			//not end of pattern, move to next char of pattern
			i++;
        }

		//characters don't match
		else {
			//use valid border to skip ahead
			if (T[i] != -1) {
				m = m + i - T[i];
				i = T[i];
            }

			//no valid border, try next char of text as start of pattern
			else {
				m++;
				i = 0;
            }
        }
    }

	return matches;
}

// pat = pattern to build partial match (prefix) table for
vector<int> buildTable(string pat) {
	vector<int> T(pat.length() + 1);

	int i = 0;		// prefix of a length 0
	int j = -1;		// no longest border defined, use -1

	T[i] = j;		// T[0] = -1

	//loop to build prefix table
	while (i < pat.length()) {			//handle entire pattern
		//try to extend the longest border of pat[0...i-1] by adding pat[i]

		while (j >= 0 && pat[i] != pat[j])	// as long as pat[i] != pat[j] (but j is not negative)
			j = T[j];	// move to next largest border

		// characters match, found border to extend OR we reached the front of T and j = -1

		//remember that T[i] corresponds to pat[0...i-1], so increment i
		i++;
		//j is the length of the border we're extending, so increment j
		j++;

		T[i] = j;	//longest border pat[0...i] is of length j
    }

	return T;
}


int main() {
    string pattern;
    while (std::getline(cin, pattern)) {
        string input;

        std::getline(cin, input);

        for (int i : kmpFind(input, pattern, buildTable(pattern), true)) {
            cout << i << " ";
        }

        cout << endl;
    }
}