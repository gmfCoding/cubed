#include "orbit.h"

void kep_elem_set(t_kep_orb *kep, double value, t_kpe prop, t_kpep prec)
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
	{
		if (prec == ELEM_EXACT)
			kep->prime_angle = prop;
		kep->set.encoded[KEP_MNA] = ELEM_NONE;
		kep->set.encoded[KEP_TA] = ELEM_NONE;
		kep->set.encoded[KEP_EA] = ELEM_NONE;
		kep->set.encoded[kep->prime_angle] = ELEM_EXACT;
	}
	kep->set.encoded[prop] = prec;
}

void kep_complete(t_kep_orb *kep)
{
	const t_kpep	ed = ELEM_DERIVED;
	double			pot_ecc;

	pot_ecc = (kep->apo - kep->per) / (kep->apo + kep->per);
	if (!kep->set.sma && kep->set.apo && kep->per)
		kep_elem_set(kep, (kep->apo + kep->per) / 2.0, KEP_SMA, ed);
	if (!kep->set.ecc && kep->set.apo && kep->per)
		kep_elem_set(kep, pot_ecc, KEP_ECC, ed); 
	if (!kep->set.apo && kep->set.sma && kep->ecc)
		kep_elem_set(kep, kep->sma * (1.0 + kep->ecc), KEP_APO, ed);
	if (!kep->set.per && kep->set.sma && kep->ecc)
		kep_elem_set(kep, kep->sma * (1.0 - kep->ecc), KEP_PER, ed);
	if (!kep->set.ea && kep->set.ta && kep->set.ecc)
		kep_elem_set(kep, orb_ta_to_ea(kep->ta, kep->ecc), KEP_EA, ed);
	if (!kep->set.ea && kep->set.mna && kep->set.ecc)
		kep_elem_set(kep, orb_ma_to_ea(kep->mna, kep->ecc), KEP_EA, ed);
	if (!kep->set.mna && kep->set.ea && kep->set.ecc)
		kep_elem_set(kep, orb_ea_to_ma(kep->ea, kep->ecc), KEP_MNA, ed);
	if (!kep->set.ta && kep->set.ea && kep->set.ecc)
		kep_elem_set(kep, orb_ea_to_ta(kep->ea, kep->ecc), KEP_TA, ed);
	kep->radius = kep->sma * (1 - kep->ecc * cos(kep->ea));
	kep->mom = sqrt(kep->self.grav * kep->sma * (1 - kep->ecc * kep->ecc));
}

void	kep_elem_reset(t_kep_orb *kep)
{
	kep->set = (t_kep_use){0};
}