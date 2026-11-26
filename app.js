document.addEventListener('DOMContentLoaded', () => {
  const form = document.getElementById('billForm');
  const invoiceOutput = document.getElementById('invoiceOutput');
  const metricsContainer = document.getElementById('metricsContainer');
  const metricEnergy = document.getElementById('metricEnergy');
  const metricFixed = document.getElementById('metricFixed');
  const metricTax = document.getElementById('metricTax');
  const metricNet = document.getElementById('metricNet');
  const copyBtn = document.getElementById('copyBtn');

  function calculate(id, name, cat, units) {
    let energy = 0;
    let fixed = 0;
    let surchargeRate = 0.05;
    let dutyRate = 0.09;
    let catName = '';

    if (cat === 1) {
      catName = 'Domestic / Residential';
      fixed = 50.0;
      if (units <= 100) {
        energy = units * 3.25;
      } else if (units <= 250) {
        energy = 100 * 3.25 + (units - 100) * 4.75;
      } else if (units <= 450) {
        energy = 100 * 3.25 + 150 * 4.75 + (units - 250) * 6.8;
      } else {
        energy = 100 * 3.25 + 150 * 4.75 + 200 * 6.8 + (units - 450) * 8.9;
      }
    } else if (cat === 2) {
      catName = 'Commercial Enterprise';
      fixed = 160.0;
      surchargeRate = 0.07;
      dutyRate = 0.12;
      if (units <= 150) {
        energy = units * 7.1;
      } else if (units <= 400) {
        energy = 150 * 7.1 + (units - 150) * 9.2;
      } else {
        energy = 150 * 7.1 + 250 * 9.2 + (units - 400) * 11.5;
      }
    } else {
      catName = 'Industrial Heavy Load';
      fixed = 450.0;
      surchargeRate = 0.08;
      dutyRate = 0.15;
      if (units <= 500) {
        energy = units * 9.8;
      } else {
        energy = 500 * 9.8 + (units - 500) * 13.6;
      }
    }

    const surcharge = energy * surchargeRate;
    const duty = (energy + fixed) * dutyRate;
    const gross = energy + fixed + surcharge + duty;
    const discount = gross * 0.02;
    const net = gross - discount;

    return { id, name, catName, units, energy, fixed, surcharge, duty, gross, discount, net };
  }

  function renderBill(b) {
    const text = 
`=================================================================
                  WATTWISE UTILITY SERVICES                       
               OFFICIAL CONSUMER ELECTRICITY BILL                 
=================================================================
 Consumer ID   : ${b.id.padEnd(20)}  Date Generated: 2026-11-26
 Consumer Name : ${b.name.padEnd(20)}  Category      : ${b.catName}
 Units Consumed: ${b.units.toFixed(2).padEnd(10)} kWh          Billing Cycle : Monthly
-----------------------------------------------------------------
 CHARGE BREAKDOWN                                     AMOUNT (INR)
-----------------------------------------------------------------
 1. Energy Charges (Tiered Slab Calculation)   :  Rs ${b.energy.toFixed(2).padStart(10)}
 2. Fixed Infrastructure / Meter Charge        :  Rs ${b.fixed.toFixed(2).padStart(10)}
 3. Regulatory Surcharge                       :  Rs ${b.surcharge.toFixed(2).padStart(10)}
 4. State Electricity Duty & Taxes             :  Rs ${b.duty.toFixed(2).padStart(10)}
-----------------------------------------------------------------
 GROSS INVOICE TOTAL                           :  Rs ${b.gross.toFixed(2).padStart(10)}
 Prompt Settlement Incentive (2.0% Discount)   : -Rs ${b.discount.toFixed(2).padStart(10)}
=================================================================
 NET AMOUNT PAYABLE                            :  Rs ${b.net.toFixed(2).padStart(10)}
=================================================================
 Please settle before the 15th to avail prompt settlement discount.`;

    invoiceOutput.textContent = text;
    metricEnergy.textContent = `Rs ${b.energy.toFixed(2)}`;
    metricFixed.textContent = `Rs ${b.fixed.toFixed(2)}`;
    metricTax.textContent = `Rs ${(b.surcharge + b.duty).toFixed(2)}`;
    metricNet.textContent = `Rs ${b.net.toFixed(2)}`;
    metricsContainer.style.display = 'grid';
  }

  form.addEventListener('submit', (e) => {
    e.preventDefault();
    const id = document.getElementById('consumerId').value.trim();
    const name = document.getElementById('consumerName').value.trim();
    const cat = parseInt(document.getElementById('category').value, 10);
    const units = parseFloat(document.getElementById('units').value);

    const bill = calculate(id, name, cat, units);
    renderBill(bill);
  });

  copyBtn.addEventListener('click', () => {
    navigator.clipboard.writeText(invoiceOutput.textContent).then(() => {
      copyBtn.textContent = 'Copied!';
      setTimeout(() => { copyBtn.textContent = 'Copy Invoice Text'; }, 2000);
    });
  });

  // Initial calculation
  const initialBill = calculate('CON-8421', 'Raghav Mehta', 1, 280);
  renderBill(initialBill);
});
