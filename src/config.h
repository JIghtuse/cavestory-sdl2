#ifndef CONFIG_H_
#define CONFIG_H_

namespace config {

enum class GraphicsQuality {
    HIGH,
    ORIGINAL
};

GraphicsQuality getGraphicsQuality();

} /* namespace config */

#endif /* CONFIG_H_ */
