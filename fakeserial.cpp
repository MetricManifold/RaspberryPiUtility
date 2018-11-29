
#include "fakeserial.h"


/*
 * read the data from the arduino port
 * @buffer The data to read from the serial port
 * @buf_size The size of the data buffer in bytes
 * @returns Integer representing the bytes that have been read in
 */
int FakeSerial::read(char *buffer, unsigned int buf_size)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<> dis(-10.0, 10.0);

	yaw += dis(gen);
	pitch += dis(gen);

	yaw = min(yaw, 360);
	yaw = max(yaw, 0);

	pitch = min(pitch, 360);
	pitch = max(pitch, 0);

	ce::coords_to_char(yaw, pitch, buffer);

	char data[BIT_LENGTH + 1];
	ce::print_as_bits(buffer, data);

	printf("SERIAL_OUT: %s, (%lf/%lf)\n", data, yaw, pitch);
	return true;
}

/*
 * write the data into the arduio port
 * @buffer The data to write into the serial port
 * @buf_size The size of the data buffer in bytes
 * @returns Whether the write is successful (true) or not (false)
 */
bool FakeSerial::write(char *buffer, unsigned int buf_size)
{
	auto[yaw, pitch] = ce::bytes_to_coords(buffer);
	char data[BIT_LENGTH + 1];

	ce::print_as_bits(buffer, data);
	printf("SERIAL_IN: %s, (%lf/%lf)\n", data, yaw, pitch);

	return true;
}
