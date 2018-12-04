
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

	yaw = std::min(yaw, 360.);
	yaw = std::max(yaw, 0.);

	pitch = std::min(pitch, 360.);
	pitch = std::max(pitch, 0.);

	ce::coords_to_char(yaw, pitch, buffer);

	char output[BIT_LENGTH + 1];
	ce::print_as_bits(buffer, output);
	printf("SERIAL_OUT: %s, (%lf/%lf)\n", output, yaw, pitch);

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
#ifdef _WIN64
	auto[yaw, pitch] = ce::bytes_to_coords(buffer);
#else
        auto coords = ce::bytes_to_coords(buffer);
        double yaw = std::get<0>(coords);
        double pitch = std::get<1>(coords);
#endif
	

	char output[BIT_LENGTH + 1];
	ce::print_as_bits(buffer, output);
	printf("SERIAL_IN: %s, (%lf/%lf)\n", output, yaw, pitch);

	return true;
}
