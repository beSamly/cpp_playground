#include <pulsar/Client.h>

#include <thread>

using namespace pulsar;

int main() {
  Client client("pulsar://localhost:6650");

  Producer producer;

  Result result =
      client.createProducer("persistent://public/default/my-topic", producer);
  if (result != ResultOk) {
    std::cout << "Error creating producer: " << result << std::endl;
    return -1;
  }

  // Send 100 messages synchronously
  /*int ctr = 0;
  while (ctr < 100) {
    std::string content = "msg" + std::to_string(ctr);
    Message msg =
        MessageBuilder().setContent(content).setProperty("x", "1").build();
    Result result = producer.send(msg);
    if (result != ResultOk) {
      std::cout << "The message " << content
                << " could not be sent, received code: " << result << std::endl;
    } else {
      std::cout << "The message " << content << " sent successfully"
                << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ctr++;
  }

  std::cout << "Finished producing synchronously!" << std::endl;*/

  client.close();
  return 0;
}