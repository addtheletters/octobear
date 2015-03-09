
int ensurePositive(int val) {
	if (val < 0) {
		return 0;
	}
	return val;
}

int ensureCapped(int val, int cap) {
	if (val > cap) {
		return cap;
	}
	return val;
}
