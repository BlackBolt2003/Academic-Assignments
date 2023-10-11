import "./globals.css";
import type { Metadata } from "next";
import { Inter } from "next/font/google";

const inter = Inter({ subsets: ["latin"] });

export const metadata: Metadata = {
  title: "Hungry Hub - Your Culinary Connection",
  description:
    "Welcome to Hungry Hub, your ultimate destination for satisfying your cravings. Discover a world of culinary delights at your fingertips. Order from a diverse selection of restaurants, explore mouthwatering menus, and enjoy fast, convenient deliveries right to your doorstep. Hungry Hub is your trusted partner for a delicious dining experience. Join us today and let your taste buds embark on a flavorful journey!",
};

export default function RootLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <html lang="en">
      <body className={inter.className}>{children}</body>
    </html>
  );
}
