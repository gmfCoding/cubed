#include "orbit.h"

void kep_elem_set(t_kep_orb *kep, double value, t_kpe prop)
{
	if (prop == KEP_SMA)
		kep->sma = value;
	if (prop == KEP_APO)
		kep->apo = value;
	if (prop == KEP_PER)
		kep->per = value;
	else if (prop == KEP_ECC)
		kep->ecc = value;
	else if (prop == KEP_AOP)
		kep->aop = value;
	else if (prop == KEP_LAN)
		kep->lan = value;
	else if (prop == KEP_INC)
		kep->inc = value;
	if (prop == KEP_MNA)
		kep->mna = value;
	else if (prop == KEP_TA)
		kep->ta = value;
	else if (prop == KEP_EA)
		kep->ea = value;
	if (prop == KEP_MNA || prop == KEP_TA || prop == KEP_EA)
		kep->set.encoded &= ~(KEP_MNA2 | KEP_TA2 | KEP_EA2);
	kep->set.encoded |= (int)(double)pow(2.0, (double)prop);
}

void kep_complete(t_kep_orb *kep)
{
	if (!kep->set.sma && kep->set.apo && kep->per)
		kep_elem_set(kep, (kep->apo + kep->per) / 2.0, KEP_SMA);
	if (!kep->set.ecc && kep->set.apo && kep->per)
		kep_elem_set(kep, (kep->set.apo - kep->set.per) / (kep->set.apo + kep->set.per), KEP_ECC); 
	if (!kep->set.apo && kep->set.sma && kep->ecc)
		kep_elem_set(kep, kep->sma * (1.0 + kep->ecc), KEP_APO);
	if (!kep->set.per && kep->set.sma && kep->ecc)
		kep_elem_set(kep, kep->sma * (1.0 - kep->ecc), KEP_PER);
	if (!kep->set.ea && kep->set.ta && kep->set.ecc)
		kep_elem_set(kep, orb_ta_to_ea(kep->ta, kep->ecc), KEP_EA);
	if (!kep->set.ea && kep->set.mna && kep->set.ecc)
		kep_elem_set(kep, orb_ma_to_ea(kep->mna, kep->ecc), KEP_EA);
	if (!kep->set.mna && kep->set.ea && kep->set.ecc)
		kep_elem_set(kep, orb_ea_to_ma(kep->ea, kep->ecc), KEP_MNA);
	if (!kep->set.ta && kep->set.ea && kep->set.ecc)
		kep_elem_set(kep, orb_ea_to_ta(kep->ea, kep->ecc), KEP_TA);
}