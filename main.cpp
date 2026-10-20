#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// Hook a PlayerObject
class $modify(MyPlayerObject, PlayerObject) {
    void pushButton(PlayerButton p0) {
        auto playLayer = PlayLayer::get();
        
        // Solo actuar si estamos dentro de un nivel jugando
        if (!playLayer) {
            PlayerObject::pushButton(p0);
            return;
        }

        // Leer la configuración del rango (en frames)
        int frameRange = Mod::get()->getSettingValue<int64_t>("click-range");

        // Guardar estado actual de simulación
        // NOTA: Para predecir si mueres, la forma más precisa en GD es
        // revisar la colisión en el frame actual vs el micro-offset de frames.
        
        bool originalClickIsFatal = this->m_isDead; 

        // Si el click en este instante provocaría una colisión/muerte:
        // (Aquí llamarías a tu función comprobadora de colisión)
        if (wouldDieOnCurrentFrame(this, p0)) {
            
            bool foundSafeFrame = false;

            // Buscar en la ventana de frames si hay un timing seguro
            for (int offset = -frameRange; offset <= frameRange; offset++) {
                if (!wouldDieWithOffset(this, p0, offset)) {
                    // ¡Encontramos un frame seguro!
                    // Aplicamos el click corregido
                    PlayerObject::pushButton(p0);
                    foundSafeFrame = true;
                    
                    // Opcional: mostrar un indicador visual o log
                    log::info("Click corregido con un desfase de {} frames", offset);
                    break;
                }
            }

            // Si no se encontró ningún punto seguro en ese rango, 
            // se deja el click normal (o se ignora para no morir).
            if (!foundSafeFrame) {
                // Opción A: Dejar que muera
                PlayerObject::pushButton(p0);
            }
        } else {
            // El click original era seguro, se ejecuta normal
            PlayerObject::pushButton(p0);
        }
    }

    // Función auxiliar lógica para probar la colisión
    bool wouldDieOnCurrentFrame(PlayerObject* player, PlayerButton button) {
        // Lógica para comprobar si 'player->m_isDead' se activa tras el paso físico
        return false; // Implementar verificación de hitboxes / colisiones de PlayLayer
    }

    bool wouldDieWithOffset(PlayerObject* player, PlayerButton button, int frameOffset) {
        // Lógica de simulación física en un sub-frame o simulación de física
        return false; 
    }
};
