#if !defined(SEN0208_H)
#define SEN0208_H
#endif // SEN0208_H

/** Initialiser le capteur de distance SEN0208
 */
void init_SEN0208();

/** Lire la distance mesurée par le capteur SEN0208
 * [OUT] Distance mesurée moyennée
 */
int distance();

/** Lire la distance mesurée par le capteur SEN0208
 * [OUT] Distance mesurée
 */
int once_Distance();

/** Lire la distance mesurée par le capteur SEN0208 mode 0
 *  Mode 0: Mode=floating high level (PWM) pulse width output
 */
int distance_mode_0();

/** Lire la distance mesurée par le capteur SEN0208 mode 4
 *  Mode=360K low power consumption (PWM) high level pulse width controlled output
 */
int distance_mode_4();