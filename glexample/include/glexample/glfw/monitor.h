
//{
//  int monitors_count;
//  GLFWmonitor **monitors = glfwGetMonitors(&monitors_count);
//  std::cout << "monitors: " << monitors_count << std::endl;
//
//  for (size_t i = 0; i < monitors_count; i++) {
//    GLFWmonitor *monitor = *(monitors + i);
//    std::cout << "monitor: " << glfwGetMonitorName(monitor) << std::endl;
//
//    int modes_count;
//    const GLFWvidmode *modes = glfwGetVideoModes(monitor, &modes_count);
//    const GLFWvidmode *current_mode = glfwGetVideoMode(monitor);
//    std::cout << "modes: " << modes_count << std::endl;
//
//    for (size_t j = 0; j < modes_count; j++) {
//      const GLFWvidmode mode = *(modes + j);
//      std::cout << (current_mode == &mode ? "*" : "") << "mode: "
//                << "redBits: " << mode.redBits
//                << ", greenBits: " << mode.greenBits
//                << ", blueBits: " << mode.blueBits
//                << ", width: " << mode.width << ", height: " << mode.height
//                << ", refreshRate: " << mode.refreshRate << std::endl;
//    }
//
//    int width_mm, height_mm;
//    glfwGetMonitorPhysicalSize(monitor, &width_mm, &height_mm);
//    std::cout<<"width_mm: "<<width_mm<<", height_mm: "<<height_mm<<std::endl;
//
//    float xscale, yscale;
//    glfwGetMonitorContentScale(monitor, &xscale, &yscale);
//    std::cout<<"xscale: "<<xscale<<", yscale: "<<yscale<<std::endl;
//
//    int xpos, ypos, width, height;
//    glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);
//    std::cout<<"xpos: "<<xpos<<", ypos: "<<ypos<<", width: "<<width<<", height: "<<height<<std::endl;
//  }
//}
